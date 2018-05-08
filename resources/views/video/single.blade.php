@extends('layouts.app')

@section('content')
<div class="container">
    <div class="row justify-content-center">
        <div class="col-md-12">
            <div class="card">
                <div class="card-header">{{ $video->name }}</div>

                <div class="card-body">

                    <video width="50%" height="auto" style="background-color:#000; float:left;" controls autoplay>
                        <source src="{{ asset("storage/original_videos/$video->id.mp4") }}" type="video/mp4">
                        Your browser does not support the video.
                    </video>

                    <video width="50%" height="auto" style="background-color:#000; float:left;" controls autoplay>
                        <source src="{{ asset("storage/processed_videos/$video->id.mp4") }}" type="video/mp4">
                        Your browser does not support the video.
                    </video>

                </div>
            </div>
        </div>
    </div>
</div>
@endsection
