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
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        $user = User::find($id);

        return response()->json($user);
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
            'first_name'       => 'string|max:255',
            'last_name'        => 'string|max:255',
            'email'            => 'string|email|max:255|unique:users',
            'new_password'     => 'string|string|min:6|confirmed',
            //'current_password' => 'required|string',
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
        $input = $request->except(['password_confirmation']);
        $this->validator($request->all())->validate();

        $user = User::find($id);
        foreach ($input as $key => $value) {
            $user->$key = $value;
        }
        $user->save();

        return response()->json($user);
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

        return response()->json(User::all());
    }
}