@extends('layouts.app')

@section('content')
<div class="container">
    <div class="jumbotron text-center">
        <h1 class="display-4">
          Welcome to StackUnderflow
          <img
            class='mr-2'
            src="{{ asset('icons/logo.svg') }}"
            width="100"
            height="100"
            alt=""
          />
        </h1>
        <p class="lead">
          We add a box-filter on your face for free!
        </p>
        <hr class="my-4">
        <a href="/home" class="btn btn-primary" role="button">
            Try Now
        </a>
    </div>
</div>
@endsection
