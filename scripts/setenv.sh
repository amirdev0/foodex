#!/bin/bash

echo "Required packages for development:"
echo "libgtk-3-0 libgtk-3-dev make gcc pkg-config  mysql-server libmysqlclient-dev"
echo

if [[ $PWD =~ "scripts" ]]; then
	cd ..
fi

if [ ! -f "./mysql/setdb.sql" -a -f "./mysql/ddl.sql" -a -f "./mysql/filldb.sql" ]; then
	echo "SQL files in 'mysql/' directory were not found"
	exit 1
fi

#sudo mysql <<< exit 2>/dev/null
#if [ $? -ne 0 ]; then
#	mysqladmin -u$DBUSER -p$DBPASS password '' 2>/dev/null
#fi

source .env.example
FILE="./mysql/setdb.sql"
sed -i "s/username/'$DBUSER'/" $FILE
sed -i "s/hostname/'$DBHOST'/" $FILE
sed -i "s/password;/'$DBPASS';/" $FILE
sed -i "s/database/$DBNAME/" $FILE

mysql -u$DBUSER -p$DBPASS < ./mysql/setdb.sql
mysql -u$DBUSER -p$DBPASS $DBNAME < ./mysql/ddl.sql
mysql -u$DBUSER -p$DBPASS $DBNAME < ./mysql/filldb.sql

exit 0
