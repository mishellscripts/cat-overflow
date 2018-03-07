<?php

use Illuminate\Http\Request;

/*
|--------------------------------------------------------------------------
| API Routes
|--------------------------------------------------------------------------
|
| Here is where you can register API routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| is assigned the "api" middleware group. Enjoy building your API!
|
*/

Route::middleware('auth:api')->get('/user', function (Request $request) {
    return $request->user();
});

// Route::post('upload', 'NoteController@store');

Route::get('user/{id}', 'UserController@show');

Route::get('user/{id}/edit', 'UserController@edit');

Route::put('user/{id}', 'UserController@update');

Route::delete('user/{id}', 'UserController@destroy');

Route::get('originalVideos', 'OriginalVideoController@index');

Route::post('uploadVideo', 'OriginalVideoController@store');
