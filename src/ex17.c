# include <stdio.h>
# include <assert.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

# define MAX_DATA 512
# define MAX_ROWS 100

struct Address {
  char *name;
  char *email;
  int row_id;
  int set;
};

struct Database {
  struct Address *rows; // rows is a pointer to an array of Address structs
  int max_rows; // max number of rows allowed in db
  int max_data; // max data size for field in row
};

struct Connection {
  FILE *file;
  struct Database *db;
};

/* declare close to be used in die */
void Database_close(struct Connection *conn);

/* abort program and clean up db connection */
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

/* print addr / row */
void Address_print(struct Address *addr) {
  printf("%d %s %s\n", addr->row_id, addr->name, addr->email);
}

/* create DB */
void Database_create(struct Connection *conn, int max_rows, int max_data) {
  int i = 0;

  // add max_rows
  conn->db->max_rows = max_rows;
  // add max_data
  conn->db->max_data = max_data;

  // allocate space for all Address structs
  conn->db->rows = malloc(sizeof(struct Address) * max_rows);

  // fill out address row
  for (i = 0; i < conn->db->max_rows; i++) {
    // make a prototype to initialize it
    struct Address addr = { .row_id = i, .set = 0 };
    // set name and email
    addr.name = malloc(max_data * sizeof(char));
    addr.name = memset(addr.name, ' ', max_data);
    addr.email = malloc(max_data * sizeof(char));
    addr.email = memset(addr.email, ' ', max_data);
    // set value at memory address to address struct
    conn->db->rows[i] = addr;
  }
}

/* write database in-memory to file on disk */
void Database_write(struct Connection *conn) {
  int rc;
  struct Address *row;

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
    row = conn->db->rows + i;
    rc = fwrite(&row->row_id, sizeof(row->row_id), 1, conn->file);
    if (rc != 1) {
      die("Failed to load database.", conn);
    }
    rc = fwrite(&row->set, sizeof(row->set), 1, conn->file);
    if (rc != 1) {
      die("Failed to load database.", conn);
    }
    rc = fwrite(row->name, sizeof(*row->name) * conn->db->max_data, 1, conn->file);
    if (rc != 1) {
      die("Failed to load database.", conn);
    }
    rc = fwrite(row->email, sizeof(*row->email) * conn->db->max_data, 1, conn->file);
    if (rc != 1) {
      die("Failed to load database.", conn);
    }
  }

  rc = fflush(conn->file);
  if (rc == -1) {
    die("Cannot flush database.", conn);
  }
}

/* load db from file into memory */
void Database_load(struct Connection *conn) {
  int rc, i;
  struct Address *row;

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
    row = conn->db->rows + i;
    rc = fread(&row->row_id, sizeof(row->row_id), 1, conn->file);
    if (rc != 1) {
      die("Failed to load database.", conn);
    }
    rc = fread(&row->set, sizeof(row->set), 1, conn->file);
    if (rc != 1) {
      die("Failed to load database.", conn);
    }
    // allocate space for name and email parts of row..
    row->name = malloc(sizeof(*row->name) * conn->db->max_data);
    row->email = malloc(sizeof(*row->email) * conn->db->max_data);
    // read both
    rc = fread(row->name, sizeof(*row->name) * conn->db->max_data, 1, conn->file);
    if (rc != 1) {
      die("Failed to load database.", conn);
    }
    rc = fread(row->email, sizeof(*row->email) * conn->db->max_data, 1, conn->file);
    if (rc != 1) {
      die("Failed to load database.", conn);
    }
  }
}

/* open db connection */
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

/* close db connection */
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

/* set row in db */
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

/* get row from db */
void Database_get(struct Connection *conn, int row_id) {
  struct Address *addr = &conn->db->rows[row_id];

  if (addr->set) {
    Address_print(addr);
  } else {
    die("ID is not set", conn);
  }
}

void *Database_find(struct Connection *conn, char *field_name, char *field_value) {
  // ignore non valid attrs
  if (strcmp(field_name, "name") != 0 && strcmp(field_name, "email") != 0) {
    die("Must choose a field that exists", conn);
  }

  struct Address *addr;
  int i = 0;

  // look through each record for a match
  for (i = 0; i < conn->db->max_rows; i++) {
    addr = &conn->db->rows[i];

    if (strcmp(field_name, "name") == 0) {
      if (strcmp(addr->name, field_value) == 0) {
        return addr;
      }
    }
    if (strcmp(field_name, "email") == 0) {
      if (strcmp(addr->email, field_value) == 0) {
        return addr;
      }
    }
  }

  return NULL;
}

/* delete row from db */
void Database_delete(struct Connection *conn, int row_id) {
  // temp local address with id and set values defined
  struct Address addr = { .row_id = row_id, .set = 0 };
  // set name and email
  addr.name = malloc(conn->db->max_data * sizeof(char));
  addr.name = memset(addr.name, ' ', conn->db->max_data);
  addr.email = malloc(conn->db->max_data * sizeof(char));
  addr.email = memset(addr.email, ' ', conn->db->max_data);
  // copied into rows array
  conn->db->rows[row_id] = addr;
}

/* list all records in db */
void Database_list(struct Connection *conn) {
  int i = 0;
  struct Database *db = conn->db;

  for (i = 0; i < db->max_rows; i++) {
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

  // get row id for actions that require it
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
    case 'f':
      if (argc != 5) {
        die("Need a field name and value", conn);
      }
      void *addr;
      char *field_name = malloc(strlen(argv[3]) + 1);
      char *field_value = malloc(strlen(argv[4]) + 1);
      strcpy(field_name, argv[3]);
      strcpy(field_value, argv[4]);
      addr = Database_find(conn, field_name, field_value);
      if (addr) {
        printf("Found field %s with value %s\n", field_name, field_value);
        Address_print(addr);
      }
      break;
    default:
      die("Invalid action: c=create, g=get, s=set, d=del, l=list", conn);
  }

  return 0;
}
