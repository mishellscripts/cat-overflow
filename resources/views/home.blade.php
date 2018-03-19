@extends('layouts.app')

@section('content')

<div class="container">
    <div class="row justify-content-center">
        <div class="col-md-8">
            <div class="card">
                <div class="card-header">Upload Your Videos</div>
                <div class="card-body">
                    <div id="FileUploader" data-token="{{ $token }}"></div>
                </div>
            </div>
            <div class="card mt-5">
                <div class="card-header">Your Videos</div>
                <div class="card-body">
                  <ul class="list-group text-center">
                      @foreach ($videos as $index => $video)
                          <li class="list-group-item"><a href="/originalVideos/{{$video->id}}"> {{ $video->name }}</a></li>
                      @endforeach
                  </ul>
                </div>
            </div>
        </div>
    </div>
</div>

@endsection
