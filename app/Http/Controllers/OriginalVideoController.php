<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\OriginalVideo;
use App\User;
use App\Http\Resources\OriginalVideo as OriginalVideoResource;
use Illuminate\Support\Facades\Log;

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
        // $file = $request->file;
        // Log::info($file);
        // Log::info(filesize($file));
        $token = $request->token;
        $user = User::where('api_token', $token)->firstOrFail();
        $video = new OriginalVideo;
        $video->num_frames = 24;
        $video->fps = 25;
        $video->width = 300;
        $video->height = 400;
        $video->user_id = $user->id;
        if ($video->save()) {
            $path = $request->file('file')->storeAs('original_videos', $video->id.'.mp4');
            Log::info($path);
            return new OriginalVideoResource($video);
        } else {
          Log::warning('failed to save video');
        }

    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        //
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
