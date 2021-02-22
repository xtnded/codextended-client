#include "shared.h"
#include "script.h"

#ifdef uMYSQL

#pragma comment(lib, "libmysql.lib")
#include "mysql.h"

MYSQL *db = NULL;

void mysql_test() {
	return;
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "localhost";
	char *user = "root";
	char *password = ""; /* set me first */
	char *database = "mysql";
	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, server,
		user, password, database, 0, NULL, 0)) {
		MsgBox(va("%s\n", mysql_error(conn)));
		exit(1);
	}
	/* send SQL query */
	if (mysql_query(conn, "show tables")) {
		MsgBox(va("%s\n", mysql_error(conn)));
		exit(1);
	}
	res = mysql_use_result(conn);
	/* output table name */
	printf("MySQL Tables in mysql database:\n");
	while ((row = mysql_fetch_row(res)) != NULL)
		MsgBox(va("%s \n", row[0]));
	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);
}

void GScr_mysql_get_connection(int a1) {
	if (db != NULL) {
		Scr.AddInt((int)db);
	}
	else {
		Scr.AddUndefined();
	}
}

void GScr_mysql_init(int entityIndex) {
	MYSQL *connection = mysql_init(NULL);
	if (connection != NULL)
		Scr.AddInt((int)connection);
	else
		Scr.AddUndefined();
}

void GScr_mysql_real_connect(int entityIndex) {
	MYSQL *m = (MYSQL*)Scr.GetInt(0);
	char* hostname = Scr.GetString(1);
	char* username = Scr.GetString(2);
	char* password = Scr.GetString(3);
	char* database = Scr.GetString(4);
	int port = Scr.GetInt(5);
	if (m != NULL) {
		MYSQL *c = mysql_real_connect(m, hostname, username, password, database, port, NULL, 0);
		my_bool reconnect = 1;
		mysql_options(c, MYSQL_OPT_RECONNECT, &reconnect);
		Scr.AddInt((int)c);
	}
	else {
		Scr.AddUndefined();
	}
}

void GScr_mysql_connect_global(int n) {
	static bool connected = false;

	char* hostname = Scr.GetString(0);
	char* username = Scr.GetString(1);
	char* password = Scr.GetString(2);
	char* database = Scr.GetString(3);
	int port = Scr.GetInt(4);

	if (connected) {
		Scr.AddInt((int)db);
		return;
	}

	if (db != NULL) {
		db = mysql_real_connect(db, hostname, username, password, database, port, NULL, 0);
		connected = true;
		my_bool reconnect = 1;
		mysql_options(db, MYSQL_OPT_RECONNECT, &reconnect);
		Scr.AddInt((int)db);
	}
	else
		Scr.AddUndefined();
}

void scr_mysql_global_cleanup() {
	if (db != NULL) {
		mysql_close(db);
		mysql_library_end();
		db = NULL;
	}
}

void scr_mysql_global_startup() {
	db = mysql_init(NULL);

	if (db == NULL) {
		MsgBox("mysql_init failed!");
	}
}

void GScr_mysql_error(int entityIndex) {
	MYSQL *m = (MYSQL*)Scr.GetInt(0);
	Scr.AddString((char*)mysql_error(m));
}

void GScr_mysql_errno(int entityIndex) {
	MYSQL *m = (MYSQL*)Scr.GetInt(0);
	Scr.AddInt(mysql_errno(m));
}

void GScr_mysql_close(int entityIndex) {
	MYSQL *m = (MYSQL*)Scr.GetInt(0);
	mysql_close(m);
}

void GScr_mysql_query(int entityIndex) {
	MYSQL *m = (MYSQL*)Scr.GetInt(0);
	char* query = Scr.GetString(1);
	Scr.AddInt((int)mysql_query(m, query));
}

void GScr_mysql_affected_rows(int entityIndex) {
	MYSQL *m = (MYSQL*)Scr.GetInt(0);
	Scr.AddInt((int)mysql_affected_rows(m));
}

void GScr_mysql_store_result(int entityIndex) {
	MYSQL *m = (MYSQL*)Scr.GetInt(0);
	Scr.AddInt((int)mysql_store_result(m));
}

void GScr_mysql_num_rows(int entityIndex) {
	MYSQL_RES *m = (MYSQL_RES*)Scr.GetInt(0);
	Scr.AddInt((int)mysql_num_rows(m));
}

void GScr_mysql_num_fields(int entityIndex) {
	MYSQL_RES *m = (MYSQL_RES*)Scr.GetInt(0);
	Scr.AddInt((int)mysql_num_fields(m));
}

void GScr_mysql_field_seek(int entityIndex) {
	MYSQL_RES *m = (MYSQL_RES*)Scr.GetInt(0);
	int offset = Scr.GetInt(1);
	Scr.AddInt((int)mysql_field_seek(m, offset));
}

void GScr_mysql_fetch_field(int entityIndex) {
	MYSQL_RES *res = (MYSQL_RES*)Scr.GetInt(0);
	MYSQL_FIELD *f = mysql_fetch_field(res);
	if (!f)
		Scr.AddUndefined();
	else
		Scr.AddString(f->name);
}

void GScr_mysql_fetch_row(int a1) {
	MYSQL_RES* result = (MYSQL_RES*)Scr.GetInt(0);
	MYSQL_ROW row = mysql_fetch_row(result);
	if (!row) {
		Scr.AddUndefined();
		return;
	}

	Scr.MakeArray();

	int num = mysql_num_fields(result);
	for (int i = 0; i < num; i++) {
		if (row[i] == NULL)
			Scr.AddUndefined();
		else
			Scr.AddString(row[i]);
		Scr.AddArray();
	}
}

void GScr_mysql_free_result(int entityIndex) {
	MYSQL_RES *res = (MYSQL_RES*)Scr.GetInt(0);
	mysql_free_result(res);
}

void GScr_mysql_real_escape_string(int entityIndex) {
	MYSQL *m = (MYSQL*)Scr.GetInt(0);
	char* escape = Scr.GetString(1);
	char* str = (char*)malloc(strlen(escape) * 2 + 1);
	mysql_real_escape_string(m, str, escape, strlen(escape));
	Scr.AddString(str);
	free(str);
}
#endif