<?php

namespace App\Http\Controllers;

use Auth;
use App\User;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Hash;
use Illuminate\Support\Facades\Session;
use Illuminate\Support\Facades\Validator;
use Illuminate\Validation\Rule;

class UserController extends Controller
{
    /*
    |--------------------------------------------------------------------------
    | User Controller
    |--------------------------------------------------------------------------
    |
    | This controller handles viewing of user information, updating user information,
    | validating new user information.
    |
    */

    public function index() 
    {
        $user = Auth::user();

        return view('edit', compact('user'));
    }

    /**
     * Show the form for editing the specified user.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        $user = Auth::user();

        // Load view and pass the user
        return view('edit', compact('user'));
    }

    /**
     * Get a validator for an incoming create or update requests.
     *
     * @param  array  $data
     * @return \Illuminate\Contracts\Validation\Validator
     */
    protected function validator(array $input, $id)
    {
        return Validator::make($input, [
            'first_name' => 'nullable|string|max:64',
            'last_name' => 'nullable|string|max:64',
            'email' => [
                'string',
                'email',
                'max:128',
                Rule::unique('users')->ignore($id),
            ],
            'password' => 'nullable|string|min:6|confirmed',
        ]);
    }

    /**
     * Update the specified user in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, $id)
    {
        $input = $request->except(['password_confirmation', '_token', '_method']);
        $this->validator($request->all(), $id)->validate();
        $user = Auth::user();

        foreach ($input as $key => $value) {
            // Change non-empty inputs that are different values from before.
            if ($value && $user->key != $value) {
                $user->$key = $key=='password' ? Hash::make($value) : $value;
            }
        }
        $user->save();
        Session::flash('success', 'Settings changed successfully!');

        return redirect()->back();
    }
}