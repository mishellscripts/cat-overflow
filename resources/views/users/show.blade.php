@extends('layouts.app')

@section('content')
<ul>
    <li>User id: {{ $user->user_id }}</li>
    <li>Username: {{ $user->username }}</li>
    <li>Name: {{ $user->first_name }} {{ $user->last_name }}</li>
    <li>Email: {{ $user->email }}</li>
</ul>
@endsection