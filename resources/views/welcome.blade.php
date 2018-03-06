@extends('layouts.app')

@section('content')
<div class="container">
    <div class="row justify-content-center">
        <div class="col-md-8">
            <div class="card">
                <div class="card-header">Welcome</div>

                <div class="card-body">
                    Hello! This is the welcome page. We can put the description
                    of our app here.
                    <div>
                      <a href="/home" class="btn btn-primary" role="button">
                        Try Now
                      </a>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
@endsection
