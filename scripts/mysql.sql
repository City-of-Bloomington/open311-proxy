-- @copyright 2006-2012 City of Bloomington, Indiana
-- @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
-- @author Cliff Ingham <inghamn@bloomington.in.gov>
create table people (
	id int unsigned not null primary key auto_increment,
	firstname varchar(128) not null,
	lastname varchar(128) not null,
	email varchar(255) not null,
	username varchar(40) unique,
	password varchar(40),
	authenticationMethod varchar(40),
	role varchar(30)
);

create table endpoints (
	id int unsigned not null primary key auto_increment,
	url varchar(255) not null,
	name varchar(128) not null,
	jurisdiction varchar(128),
	api_key varchar(128)
);

create table clients (
	id int unsigned not null primary key auto_increment,
	url varchar(255) not null,
	name varchar(128) not null unique,
	endpoint_id int unsigned not null,
	foreign key (endpoint_id) references endpoints(id)
);