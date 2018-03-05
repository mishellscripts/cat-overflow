<?php

namespace App\Http\Controllers;

use Auth;
use App\User;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Hash;
use Illuminate\Support\Facades\Validator;

class UserController extends Controller
{
    /*
    |--------------------------------------------------------------------------
    | User Controller
    |--------------------------------------------------------------------------
    |
    | This controller handles the API requests for viewing user information,
    | updating user information, and deletion of user.
    |
    */

    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        $this->middleware('auth');
    }

    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index(Request $request)
    {
        // Get all the users
        $users = User::all();

        // JSON Response
        return $users;

        // Load view and pass the users
        // return view('users.index', compact('users'));
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        $user = User::find($id);

        // JSON Response
        return response()->json($user);

        // Load view and pass the user
        // return view('users.show', compact('user'));

    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        $user = User::find($id);

        // Load view and pass the user
        return view('users.edit', compact('user'));
    }

    /**
     * Get a validator for an incoming create or update requests.
     *
     * @param  array  $data
     * @return \Illuminate\Contracts\Validation\Validator
     */
    protected function validator(array $input)
    {
        return Validator::make($input, [
            'first_name' => 'string|max:50',
            'last_name'  => 'string|max:50',
            'email'      => 'required|string|email|max:50|unique:account',
            'password'   => 'required|string|min:6|confirmed',
        ]);
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
        $input = $request->input();

        $this->validator($request->all())->validate();

        $user = User::find($id);
        $user->first_name = $input['first_name'];
        $user->last_name  = $input['last_name'];
        $user->email      = $input['email'];
        $user->password   = Hash::make($input['password']);
        $user->save();

        // JSON Response
        return $user;
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        $user = User::find($id);
        
        if ($user) {
            $user->delete();
        }

        // JSON Response
        return User::all();
    }
}
