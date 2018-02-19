CREATE TABLE User
(
  username CHAR(15) NOT NULL,
  password CHAR(60) NOT NULL,
  first_name VARCHAR(20) NOT NULL,
  last_name VARCHAR(20) NOT NULL,
  last_login_date TIMESTAMP NOT NULL,
  last_login_ip CHAR(15) NOT NULL,
  PRIMARY KEY (username)
);

CREATE TABLE Video
(
  num_frames INT NOT NULL,
  fps FLOAT NOT NULL,
  video_id INT NOT NULL,
  width INT NOT NULL,
  height INT NOT NULL,
  username CHAR(15) NOT NULL,
  PRIMARY KEY (video_id),
  FOREIGN KEY (username) REFERENCES User(username)
);

CREATE TABLE Image
(
  frame_num INT NOT NULL,
  yaw FLOAT NOT NULL,
  pitch FLOAT NOT NULL,
  roll FLOAT NOT NULL,
  data_points POINT[68] NOT NULL,
  of_left_pupil POINT NOT NULL,
  of_right_pupil POINT NOT NULL,
  ft_left_pupil POINT NOT NULL,
  ft_right_pupil POINT NOT NULL,
  video_id INT NOT NULL,
  FOREIGN KEY (video_id) REFERENCES Video(video_id)
);