<?php

namespace App;

use Illuminate\Notifications\Notifiable;
use Illuminate\Foundation\Auth\User as Authenticatable;

class User extends Authenticatable
{
    use Notifiable;

    /**
     * The attributes that are mass assignable.
     *
     * @var array
     */
    protected $fillable = [
        'username', 'first_name', 'last_name', 'email', 'password', 'last_login_date', 'last_login_ip', 'api_token',
    ];

    /**
     * The attributes that cannot be mass assignable.
     * 
     * @var array
     */

    protected $guarded = [
        'user_id',
    ];

    /**
     * The attributes that should be hidden for arrays.
     *
     * @var array
     */
    protected $hidden = [
        'password', 'remember_token', 'api_token',
    ];

    // Change default authentication users table name.
    protected $table = 'account';

    // Disable default creation of updated_at and created_at fields.
    public $timestamps = false;

    // Change default primary key name.
    protected $primaryKey = 'user_id';
}
