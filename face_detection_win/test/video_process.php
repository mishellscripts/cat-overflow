<?php
class VideoProcess {
    private $video_path = '';
    private $imgs_out_path = '';
    private $video_id = 0;

    private $num_frames = 0;
    private $frame_rate = 0;
    private $x = 0;
    private $y = 0;

    function __construct($in_path, $out_path, $id) {
        $this->video_path = $in_path;
        $this->imgs_out_path = $out_path;
        $this->video_id = $id;

        //$video_path = './video/2015-10-15-15-14.avi';
        //get number of frames in the video
        $this->num_frames = (int)shell_exec('ffprobe -v error -count_frames -select_streams v:0 -show_entries stream=nb_read_frames -of default=nokey=1:noprint_wrappers=1 '.$this->video_path);
        //echo num_frames;
        
        //get fps
        $fps = shell_exec('ffprobe -v error -select_streams v:0 -show_entries stream=avg_frame_rate -of default=noprint_wrappers=1:nokey=1 '.$this->video_path);
        //echo $fps;
        preg_match_all('/\d+/', $fps, $out);
        $this->frame_rate = $out[0][0] / $out[0][1];
        //echo $frame_rate;

        //get resolution
        $resolution_info = shell_exec('ffprobe -v error -of flat=s=_ -select_streams v:0 -show_entries stream=height,width '.$this->video_path);
        //echo $resolution_info;
        preg_match_all('/[1-9][0-9]+/', $resolution_info, $matches);
        //print_r($matches);
        $this->x = (int)$matches[0][0];
        $this->y = (int)$matches[0][1];

        //extract still images from video
        //$imgs_out_path = './video/imgs/';    //output directry
        shell_exec('ffmpeg -i '.$this->video_path.' -vf fps='.$this->frame_rate.' '.$this->imgs_out_path.''.$this->video_id.'.%d.png');
    }

    function get_video_path() {
        return $this->video_path;
    }

    function get_imgs_path() {
        return $this->imgs_out_path;
    }

    function get_video_id() {
        return $this->video_id;
    }

    function get_frame_rate() {
        return $this->frame_rate;
    }

    function get_num_frames() {
        return $this->num_frames;
    }

    function get_x() {
        return $this->x;
    }

    function get_y() {
        return $this->y;
    }
}

//$video = new VideoProcess('../build/demo_in/zihang.mp4', '../build/demo_in/', 101);
$vidio = new VideoProcess("./video/test.avi", "D:/OneDrive/CS/CS160/cs160_stackoverflow/face_detection_win/cmake-build-release/in", 100);

print($video->get_num_frames()."\n");
print($video->get_frame_rate()."\n");
print($video->get_x()."\n");
print($video->get_y()."\n");


    
?>
