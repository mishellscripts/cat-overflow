<?php

namespace App\Http\Controllers\Auth;

use App\Http\Controllers\Controller;
use Illuminate\Foundation\Auth\AuthenticatesUsers;
use Illuminate\Http\Request;

class LoginController extends Controller
{
    /*
    |--------------------------------------------------------------------------
    | Login Controller
    |--------------------------------------------------------------------------
    |
    | This controller handles authenticating users for the application and
    | redirecting them to your home screen.
    |
    */

    use AuthenticatesUsers;

    /**
     * Where to redirect users after login.
     *
     * @var string
     */
    protected $redirectTo = '/home';

    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        $this->middleware('guest')->except('logout');
    }

    /**
     * Change default authentication field to username.
     * 
     * @return string
     */
    public function username()
    {
        return 'username';
    }

    /**
     * Update last login date and ip in the database on login event.
     *
     * @return void
     */
    public function authenticated(Request $request, $user)
    {
        $user->last_login_date = date('Y-m-d H:i:s');

        $user->last_login_ip = $request->ip();

        $user->save();
    }
}