@extends('layouts.app')

@section('content')
<table border='1'>
    <tr>
        <th>ID</th>
        <th>Username</th>
        <th>Name</th>
        <th>Email</th>
    </tr>

    @foreach($users as $user)
        <tr>
            <td>{{ $user->user_id }}</td>
            <td>{{ $user->username }}</td>
            <td>{{ $user->first_name }} {{ $user->last_name }}</td>
            <td>{{ $user->email }}</td>

            <!-- we will also add show, edit, and delete buttons -->
            <td>
                <!-- GET /api/user/{id} -->
                <a class="btn btn-primary" href="{{ URL::to('user/' . $user->user_id) }}">Show</a>

                <!-- GET /api/user/{id}/edit -->
                <a class="btn btn-primary" href="{{ URL::to('user/' . $user->user_id . '/edit') }}">Edit</a>

                <!-- DELETE /user/{id} -->
                <form method="DELETE" action="{{ URL::to('user/' . $user->user_id) }}"
                    <button type="submit" class="btn btn-primary">Delete</button>
                </form>
            </td>
        </tr>
    @endforeach

</table>
@endsection