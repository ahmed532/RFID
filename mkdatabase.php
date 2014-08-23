<?php
  include_once 'functions.php';
  createTable('member',  //student
	'
	m_id int NOT NULL AUTO_INCREMENT,
	PRIMARY KEY (m_id),
	name VARCHAR(50),
	RFID_tag CHARACTER(12),
	mobile CHARACTER(14),
	job VARCHAR(30)
	'
  );
  createTable('logins',
  	'
  	m_logged int NOT NULL,
  	login_time TIMESTAMP,
  	login_cost NUMERIC(3,2),
  	PRIMARY KEY (login_time),
  	FOREIGN KEY (m_logged) REFERENCES member(m_id)
  	'
  );
?>
