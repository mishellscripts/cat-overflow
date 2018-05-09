# Cat Overflow
Team Stack Overflow \
Rui Li, Zihang Ruan, Rakesh Konda, Michelle Song

## Prerequisites
You will need the following installed in order to run the application.
- [Composer](https://getcomposer.org/)
- [NPM](https://nodejs.org/)
- [FFmpeg](https://www.ffmpeg.org/download.html)
- [OpenCV](https://opencv.org/releases.html)

## Installation & Startup Steps
1. Install PHP dependencies using composer.
```bash
$ composer install
```
2. Install React dependencies using npm.
```bash
$ npm install
```
3. **Important!** Run this command to create symbolic link between public/storage and storage/app/public. This is needed for FFmpeg image extraction command.
```bash
$ php artisan storage:link
```
> **Note:** If getting error message "The public/storage" directory already exists at this step, simply remove the public/storage directory.
4. Start the server
```bash
$ php artisan serve
```
5. Head to localhost:8000 to view the application!

## Notes
* To automatically compile React components, run the following
  ```bash
  $ npm run watch
  ```
* Sessions would be stored in storage/framework/sessions with the session id as the file name. The URL with the encrypted session identifier token to maintain state is included in the file but invisible to the user.
* Image extraction not working? Try the following:
    * Check the following configuration in the constructor of OriginalVideoController.php and make sure the FFmpeg is configured correctly according to where you've installed it.
      
      ```
      public $ffmpeg_path;
      public $ffmprope_path;

      public function __construct()
      {
            // Configure ffmpeg path for different OS.
            if (strtoupper(substr(PHP_OS, 0, 3)) === 'WIN') {
                  $this->ffmpeg_path = 'C:/FFMpeg/bin/ffmpeg.exe';
                  $this->ffmprope_path = 'C:/FFMpeg/bin/ffprobe.exe';
            } else {
                  $this->ffmpeg_path = '/usr/local/bin/ffmpeg';
                  $this->ffmprope_path = '/usr/local/bin/ffprobe';
            }
      }
      ```
    * Make sure that opencv binary path '<DOWNLOAD_PATH>\opencv\build\x64\vc15\bin' is in your PATH environment variable.
