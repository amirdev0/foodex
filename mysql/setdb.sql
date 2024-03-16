START TRANSACTION;

ALTER USER usename@hostname IDENTIFIED WITH caching_sha2_password BY password;

DROP DATABASE IF EXISTS database;
CREATE DATABASE database;

COMMIT;
