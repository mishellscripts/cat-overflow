DROP TABLE IF EXISTS image;
DROP TABLE IF EXISTS processed_video;
DROP TABLE IF EXISTS origin_video;
DROP TABLE IF EXISTS account;

CREATE TABLE account
(
  user_id INT PRIMARY KEY,
  username CHAR(15),
  password CHAR(60) NOT NULL,
  first_name VARCHAR(50),
  last_name VARCHAR(50),
  last_login_date TIMESTAMP NOT NULL,
  last_login_ip CHAR(15) NOT NULL,
  email VARCHAR(50) NOT NULL
);

CREATE TABLE origin_video
(
  video_id INT PRIMARY KEY,
  user_id INT,
  origin_video_path VARCHAR(255) NOT NULL,
  num_frames INT NOT NULL,
  fps FLOAT NOT NULL,
  width INT NOT NULL,
  height INT NOT NULL,
  FOREIGN KEY(user_id) REFERENCES account(user_id) ON DELETE CASCADE
);

CREATE TABLE processed_video
(
  video_id INT,
  processed_video_path VARCHAR(255) NOT NULL,
  FOREIGN KEY(video_id) REFERENCES origin_video(video_id)
);

CREATE TABLE image
(
  video_id INT,
  frame_num INT NOT NULL,
  image_path VARCHAR(255) NOT NULL,
  yaw FLOAT NOT NULL,
  pitch FLOAT NOT NULL,
  roll FLOAT NOT NULL,
  data_points POINT[68] NOT NULL,
  of_left_pupil POINT NOT NULL,
  of_right_pupil POINT NOT NULL,
  ft_left_pupil POINT NOT NULL,
  ft_right_pupil POINT NOT NULL,
  PRIMARY KEY (video_id, frame_num),
  FOREIGN KEY(video_id) REFERENCES origin_video(video_id) ON DELETE CASCADE
);