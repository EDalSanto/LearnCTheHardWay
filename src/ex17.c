# include <stdio.h>
# include <assert.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

# define MAX_DATA 512
# define MAX_ROWS 100

struct Address {
  int row_id;
  int set;
  char *name;
  char *email;
};

struct Database {
  struct Address *rows; // rows is a pointer to an Address struct
  int max_rows;
  int max_data;
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void Database_close(struct Connection *conn);

void die(const char *message, struct Connection *conn) {
  // when an error returns from a function, it usually sets an external variable
  // called errno to say exatly happened
  if (errno) {
    perror(message); // print error
  } else {
    printf("ERROR: %s\n", message);
  }

  if (conn) {
    Database_close(conn);
  }

  exit(1);
}

void Address_print(struct Address *addr) {
  printf("%d %s %s\n", addr->row_id, addr->name, addr->email);
}

void Database_create(struct Connection *conn, int max_rows, int max_data) {
  int i = 0;

  // add max_rows
  conn->db->max_rows = max_rows;
  // add max_data
  conn->db->max_data = max_data;

  // allocate space for all address structs
  conn->db->rows = malloc(sizeof(struct Address) * max_rows);

  for (i = 0; i < conn->db->max_rows; i++) {
    // make a prototype to initialize it
    struct Address addr = { .row_id = i, .set = 0 };
    // set memory address to address struct
    conn->db->rows[i] = addr;
  }
}

void Database_write(struct Connection *conn) {
  int rc;

  rewind(conn->file);

  // write max_rows to file
  rc = fwrite(&conn->db->max_rows, sizeof(conn->db->max_rows), 1, conn->file);
  if (rc != 1) {
    die("Failed to write max_rows.", conn);
  }
  // write max_data to file
  rc = fwrite(&conn->db->max_data, sizeof(conn->db->max_data), 1, conn->file);
  if (rc != 1) {
    die("Failed to write max_data.", conn);
  }
  // flush data from database to the file stream
  for (int i = 0; i < conn->db->max_rows; i++) {
    rc = fwrite((conn->db->rows + i), sizeof(struct Address), 1, conn->file);
    if (rc != 1) {
      die("Failed to write database.", conn);
    }
  }

  rc = fflush(conn->file);
  if (rc == -1) {
    die("Cannot flush database.", conn);
  }
}

void Database_load(struct Connection *conn) {
  int rc, i;

  // load max_rows from file
  rc = fread(&conn->db->max_rows, sizeof(conn->db->max_rows), 1, conn->file);
  if (rc != 1) {
    die("Failed to load max rows.", conn);
  }
  // load max_data from file
  rc = fread(&conn->db->max_data, sizeof(conn->db->max_data), 1, conn->file);
  if (rc != 1) {
    die("Failed to load max data.", conn);
  }

  // allocate space for all address structs
  conn->db->rows = malloc(sizeof(struct Address) * conn->db->max_rows);

  // read data from file into Database
  for (i = 0; i < conn->db->max_rows; i++) {

    rc = fread((conn->db->rows + i), sizeof(struct Address), 1, conn->file);
    if (rc != 1) {
      die("Failed to load database.", conn);
    }
  }
}

struct Connection *Database_open(const char *filename, char mode) {
  struct Connection *conn = malloc(sizeof(struct Connection));

  if (!conn) {
    die("Memory Error", conn);
  }

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db) {
    die("Memory Error", conn);
  }

  if (mode == 'c') {
    // create file
    conn->file = fopen(filename, "w");
  } else {
    // open file for reading and writing
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      Database_load(conn);
    }
  }

  if (!conn->file) {
    die("Failed to open the file", conn);
  }

  return conn;
}

void Database_close(struct Connection *conn) {
  if (conn) {
    if (conn->file) {
      // flushes any data still pending in the buffer to the file,
      // closes the file, and releases any memory used for the file
      fclose(conn->file);
    }
    if (conn->db) {
      free(conn->db);
    }
    free(conn);
  }
}

void Database_set(struct Connection *conn, int row_id, const char *name, const char *email) {
  // get the row_id element in rows, which is in db, which is in conn,
  // and then get its address
  struct Address *addr = &conn->db->rows[row_id];
  int max_data = conn->db->max_data;
  if (addr->set) {
    die("Already set, delete it first", conn);
  }
  addr->set = 1;
  addr->name = malloc(sizeof(max_data));
  // WARNING: bug, read the How to Break It and fix this
  char *res = strncpy(addr->name, name, max_data);
  // demonstrate the strncpy bug
  if (!res) {
    die("Email copy failed", conn);
  }

  addr->email = malloc(sizeof(max_data));
  res = strncpy(addr->email, email, max_data);
  if (!res) {
    die("Email copy failed", conn);
  }
}

// working on getting this right..at least I think set is working
void Database_get(struct Connection *conn, int row_id) {
  struct Address *addr = &conn->db->rows[row_id];

  if (addr->set) {
    Address_print(addr);
  } else {
    die("ID is not set", conn);
  }
}

void Database_delete(struct Connection *conn, int row_id) {
  // temp local address with id and set values defined
  struct Address addr = { .row_id = row_id, .set = 0 };
  // copied into rows array
  conn->db->rows[row_id] = addr;
}

void Database_list(struct Connection *conn) {
  int i = 0;
  struct Database *db = conn->db;

  for (i = 0; i < MAX_ROWS; i++) {
    struct Address *cur = &db->rows[i];

    if (cur->set) {
      Address_print(cur);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    die("USAGE: ex17 <dbfile> <action> [action params]", NULL);
  }

  char *filename = argv[1];
  char action = argv[2][0];
  struct Connection *conn = Database_open(filename, action);
  int row_id = 0;

  if (action == 'g' || action == 's' || action == 'd') {
    row_id = atoi(argv[3]);

    if (row_id >= conn->db->max_rows) {
      die("There's not that many records", conn);
    }
  }

  switch (action) {
    case 'c':
      if (argc != 5) {
        die("Need to specify a max_rows and max_data", conn);
      }
      int max_rows = atoi(argv[3]);
      int max_data = atoi(argv[4]);
      Database_create(conn, max_rows, max_data);
      Database_write(conn);
      break;
    case 'g':
      if (argc != 4) {
        die("Need an id to get", conn);
      }
      Database_get(conn, row_id);
      break;
    case 's':
      if (argc != 6) {
        die("Need id, name, email to set", conn);
      }

      Database_set(conn, row_id, argv[4], argv[5]);
      Database_write(conn);
      break;
    case 'd':
      if (argc != 4) {
        die("Need id to delete", conn);
      }

      Database_delete(conn, row_id);
      Database_write(conn);
      break;
    case 'l':
      Database_list(conn);
      break;
    default:
      die("Invalid action: c=create, g=get, s=set, d=del, l=list", conn);
  }

  return 0;
}
