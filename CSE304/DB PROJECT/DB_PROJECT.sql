CREATE TABLE User_Table(
	user_id VARCHAR2(50) PRIMARY KEY,
	user_full_name VARCHAR2(50) NOT NULL,
	password VARCHAR2(50) NOT NULL,
	email VARCHAR2(50) NOT NULL UNIQUE,
	register_date DATE NOT NULL,
	birth_date DATE DEFAULT SYSDATE,
	region VARCHAR2(60),
	status VARCHAR2(10) --ref mamun
);

CREATE TABLE Admin_Table(
	admin_id VARCHAR2(50) PRIMARY KEY,
		--??(devid) what more?? mamun??
	CONSTRAINT A_T FOREIGN KEY (admin_id) REFERENCES User_Table(user_id)
	ON DELETE CASCADE --ON UPDATE CASCADE :( oracle seems to be not allowing it :/

);






CREATE TABLE Player_Table(
	player_id VARCHAR2(50) PRIMARY KEY,
	
	
	rating NUMBER DEFAULT 0,
	match_count NUMBER DEFAULT 0,
	win_count NUMBER DEFAULT 0,
	best_score NUMBER DEFAULT 0,
	total_xp NUMBER DEFAULT 0,
		--??(devid) what more?? mamun??
	
	CONSTRAINT P_T FOREIGN KEY (player_id) REFERENCES User_Table(user_id)
	ON DELETE CASCADE

);

CREATE TABLE Section_Table(
	section_name VARCHAR2(50) PRIMARY KEY
);





CREATE TABLE Moderator_Table(
	moderator_id VARCHAR2(50) PRIMARY KEY,
	moderating_section VARCHAR2(50) NOT NULL,
	
	CONSTRAINT M_T1 FOREIGN KEY(moderating_section) REFERENCES Section_Table(section_name)
	ON DELETE SET NULL,
	CONSTRAINT M_T2 FOREIGN KEY(moderator_id) REFERENCES User_Table(user_id)
	ON DELETE CASCADE
);

CREATE TABLE Forum_Post_Table(
	post_id NUMBER PRIMARY KEY,
	post_content VARCHAR2(3000),
	post_date DATE DEFAULT SYSDATE,
	view_count NUMBER DEFAULT 0,
	reply_count NUMBER DEFAULT 0,
	section_name VARCHAR2(50),
	posted_by_id VARCHAR2(50), --mamun??
	
	CONSTRAINT F_P_T1 FOREIGN KEY(section_name) REFERENCES Section_Table(section_name),
	CONSTRAINT F_P_T2 FOREIGN KEY(posted_by_id) REFERENCES User_Table(user_id)
);




CREATE TABLE Forum_Reply_Table(
	post_id NUMBER UNIQUE,
	reply_id NUMBER UNIQUE,
	replied_by VARCHAR2(50),
	reply_content VARCHAR2(3000),
	reply_date DATE DEFAULT SYSDATE,
	
	
	
	CONSTRAINT F_R_T1 PRIMARY KEY(post_id, reply_id),
	
	CONSTRAINT F_R_T2 FOREIGN KEY (post_id) REFERENCES Forum_Post_Table(post_id)
	ON DELETE CASCADE,
	
	
	CONSTRAINT F_R_T3 FOREIGN KEY(replied_by) REFERENCES User_Table(user_id)
	ON DELETE SET NULL
);



CREATE TABLE Post_Flag_Table(
	post_id NUMBER,
	reporter_id VARCHAR2(50),
	
	CONSTRAINT P_F_T1 UNIQUE(post_id,reporter_id),
	
	CONSTRAINT P_F_T2 FOREIGN KEY(post_id) REFERENCES Forum_Post_Table(post_id)
	ON DELETE CASCADE,
	
	CONSTRAINT P_F_T3 FOREIGN KEY(reporter_id) REFERENCES User_Table(user_id)
	ON DELETE SET NULL
);

CREATE TABLE Reply_Flag_Table(
	post_id NUMBER,
	reply_id NUMBER,
	reporter_id VARCHAR2(50),
	
	CONSTRAINT R_F_T1 UNIQUE(post_id,reply_id,reporter_id),
	
	CONSTRAINT R_F_T2 FOREIGN KEY(post_id) REFERENCES Forum_Post_Table(post_id)
	ON DELETE CASCADE,
	
	CONSTRAINT R_F_T3 FOREIGN KEY(reply_id) REFERENCES Forum_Reply_Table(reply_id)
	ON DELETE CASCADE,
	
	CONSTRAINT R_F_T4 FOREIGN KEY(reporter_id) REFERENCES User_Table(user_id)
	ON DELETE SET NULL
);


CREATE TABLE Admin_Phone_Table(
	admin_id VARCHAR2(50),
	phone_number VARCHAR2(20),
	
	CONSTRAINT A_P_T1 PRIMARY KEY(admin_id,phone_number),
	
	CONSTRAINT A_P_T2 FOREIGN KEY(admin_id) REFERENCES Admin_Table(admin_id)
	ON DELETE CASCADE

);


CREATE TABLE Match_Table(
	match_id NUMBER PRIMARY KEY,
	match_date DATE DEFAULT SYSDATE,
	match_winner VARCHAR2(50) DEFAULT NULL,
	score1 NUMBER DEFAULT 0,
	score2 NUMBER DEFAULT 0,
	player1_id VARCHAR2(50),
	player2_id VARCHAR2(50),
	
	CONSTRAINT MTCH_T1 FOREIGN KEY(player1_id) REFERENCES Player_Table(player_id)
	ON DELETE SET NULL,

	CONSTRAINT MTCH_T2 FOREIGN KEY(player2_id) REFERENCES Player_Table(player_id)
	ON DELETE SET NULL

);

CREATE TABLE Tournament_Table(
	tournament_id NUMBER PRIMARY KEY,
	start_date DATE DEFAULT SYSDATE,
	end_date DATE DEFAULT SYSDATE,
	winner_id VARCHAR2(50) DEFAULT NULL,
	runnerup_id VARCHAR2(50) DEFAULT NULL,
	
	CONSTRAINT T_T1 FOREIGN KEY(winner_id) REFERENCES Player_Table(player_id)
	ON DELETE SET NULL,
	
	CONSTRAINT T_T2 FOREIGN KEY(runnerup_id) REFERENCES Player_Table(player_id)
	ON DELETE SET NULL
);

CREATE TABLE Achievement_Table(
	achievement_id NUMBER PRIMARY KEY,
	achievement_goal VARCHAR2(50) NOT NULL,
	achievement_rewardxp NUMBER NOT NULL,
	achievement_description VARCHAR2(1000)	
);


CREATE TABLE Player_Achievement_Table(
	player_id VARCHAR2(50),
	achievement_id NUMBER,
	
	CONSTRAINT P_A_T1 PRIMARY KEY(player_id, achievement_id),
	
	CONSTRAINT P_A_T2 FOREIGN KEY(player_id) REFERENCES Player_Table(player_id)
	ON DELETE CASCADE,
	
	CONSTRAINT P_A_T3 FOREIGN KEY(achievement_id) REFERENCES Achievement_Table(achievement_id)
	ON DELETE CASCADE
);


CREATE TABLE Tournament_Match_Table(
	match_id NUMBER,
	tournament_id NUMBER,
	
	CONSTRAINT T_M_T1 PRIMARY KEY(match_id, tournament_id),
	
	CONSTRAINT T_M_T2 FOREIGN KEY(match_id) REFERENCES Match_Table(match_id)
	ON DELETE CASCADE,
	
	CONSTRAINT T_M_T3 FOREIGN KEY(tournament_id) REFERENCES Tournament_Table(tournament_id)
	ON DELETE CASCADE

);





DROP TABLE Tournament_Match_Table;
DROP TABLE Player_Achievement_Table;
DROP TABLE Achievement_Table;
DROP TABLE Tournament_Table;
DROP TABLE Match_Table;
DROP TABLE Admin_Phone_Table;
DROP TABLE Reply_Flag_Table;
DROP TABLE Post_Flag_Table;
DROP TABLE Forum_Reply_Table;
DROP TABLE Forum_Post_Table;
DROP TABLE Moderator_Table;
DROP TABLE Section_Table;
DROP TABLE Player_Table;
DROP TABLE Admin_Table;
DROP TABLE User_Table;