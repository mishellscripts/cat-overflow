<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', 'HomeController@index');

//Route::get('user/{id}/edit', 'UserController@edit')->name('settings');

Route::get('/settings', 'UserController@index')->name('settings');

Auth::routes();

Route::get('/originalVideos/{id}', 'OriginalVideoController@show');

Route::get('/home', 'HomeController@index')->name('home');
