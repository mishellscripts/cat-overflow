@extends('layouts.app')

@section('content')

<div class="container">
    <div class="row justify-content-center">
        <div class="col-md-8">
            <div class="card">
                <div class="card-header">Upload Your Videos</div>

                <div class="card-body">
          
                    <div id="FileUploader" data-token="{{ $token }}"></div>
                    <ul class="list-group text-center" style="margin-top:32px;">
                        @foreach ($videos as $index => $video)
                            <li class="list-group-item"><a href="/api/originalVideos/{{$video->id}}"> Video {{ $index+1 }}</a></li>
                        @endforeach
                    </ul>
          
                </div>
            </div>
        </div>
    </div>
</div>
  
@endsection
