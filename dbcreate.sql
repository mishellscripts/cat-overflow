DROP TABLE IF EXISTS image;
DROP TABLE IF EXISTS processed_video;
DROP TABLE IF EXISTS origin_video;
DROP TABLE IF EXISTS account;

CREATE TABLE account
(
  user_id SERIAL PRIMARY KEY,
  username CHAR(15) UNIQUE NOT NULL,
  first_name VARCHAR(50),
  last_name VARCHAR(50),
  email VARCHAR(50) UNIQUE NOT NULL,
  password CHAR(60) NOT NULL,
  last_login_date TIMESTAMP NOT NULL,
  last_login_ip CHAR(15) NOT NULL,
  api_token CHAR(60) UNIQUE,
  remember_token CHAR(100) UNIQUE
);

CREATE TABLE origin_video
(
  video_id SERIAL PRIMARY KEY,
  user_id INT NOT NULL,
  origin_video_path VARCHAR(255) NOT NULL,
  num_frames INT NOT NULL,
  fps FLOAT NOT NULL,
  width INT NOT NULL,
  height INT NOT NULL,
  FOREIGN KEY(user_id) REFERENCES account(user_id) ON DELETE CASCADE
);

CREATE TABLE processed_video
(
  video_id SERIAL,
  processed_video_path VARCHAR(255) NOT NULL,
  FOREIGN KEY(video_id) REFERENCES origin_video(video_id)
);

CREATE TABLE image
(
  video_id SERIAL NOT NULL,
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

SELECT * FROM account;