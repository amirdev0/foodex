START TRANSACTION;

ALTER USER 'root'@'localhost' IDENTIFIED WITH caching_sha2_password BY 'password';

DROP DATABASE IF EXISTS FoodEx;
CREATE DATABASE FoodEx;

COMMIT;
