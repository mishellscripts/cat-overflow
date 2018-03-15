<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\OriginalVideo;
use App\User;
use App\Http\Resources\OriginalVideo as OriginalVideoResource;
use Illuminate\Support\Facades\Log;
use FFMpeg;

class OriginalVideoController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $video = OriginalVideo::paginate(15);
        return OriginalVideoResource::collection($video);
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        //
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        $token = $request->token;
        $user = User::where('api_token', $token)->firstOrFail();
        $ffmpeg_path = '/usr/local/bin/ffmpeg';
        $ffmprope_path = '/usr/local/bin/ffprobe';
        if (strtoupper(substr(PHP_OS, 0, 3)) === 'WIN') {
          $ffmpeg_path = 'C:/FFMpeg/bin/ffmpeg.exe';
          $ffmprope_path = 'C:/FFMpeg/bin/ffprobe.exe';
        }
        $ffprobe = \FFMpeg\FFProbe::create([
            'ffmpeg.binaries'  => $ffmpeg_path,
            'ffprobe.binaries' => $ffmprope_path,
        ]);
        $info = $ffprobe
            ->streams($request->file)
            ->videos()
            ->first();
        //Log::info(var_export($info, true)); // show all info

        $frame_rate = $info->get('r_frame_rate');
        // need to eval frame rate ('30000/1001') to get float
        $fps = eval("return $frame_rate;");

        $video = new OriginalVideo;
        $video->fps = $fps;
        $video->num_frames = $info->get('nb_frames');
        $video->width = $info->get('width');
        $video->height = $info->get('height');
        $video->user_id = $user->id;

        if ($video->save()) {
            $path = $request
                ->file('file')
                ->storeAs('public/original_videos', $video->id.'.mp4');
            return new OriginalVideoResource($video);
        } else {
            Log::warning('failed to save video');
        }
        return response('Failed to store video');
    }

    /**
     * Display the specified resource.
     *
     * @param  int
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        $video = OriginalVideo::findOrFail($id);
        return view('video.single', compact('video'));
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        //
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, $id)
    {
        //
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        // Get note
        $video = OriginalVideo::findOrFail($id);

        if ($video->delete()) {
          return new OriginalVideoResource($video);
        }
    }
}
