import React, { Component } from 'react';
import ReactDOM from 'react-dom';
import axios, { post } from 'axios';
import { status } from '../util/status';
import moment from 'moment';
import Moment from 'react-moment';
import 'moment-timezone';

export default class VideoList extends Component {
    handleDelete(e) {
        e.preventDefault();
        this.deleteVideo(e.target.id).then((response) => {
            console.log(response.data);
            this.props.updateVideoList();
        })
        .catch( (error) => {
          console.log(error);
        });
    }

    deleteVideo(id) {
        const url = 'http://localhost:8000/api/deleteOriginalVideo';
        const formData = new FormData();
        formData.append('id', id);
        formData.append('token', this.props.token);
        const config = {
            headers: {
                'content-type': 'multipart/form-data'
            }
        }
        return post(url, formData, config);
    }

    render() {
        var videoList = [];
        var isEmpty = false;
        this.props.videos.forEach(function(video) {
            videoList.push(
                <a
                  key={video.id}
                  href={"/originalVideos/" + video.id}
                  className="list-group-item list-group-item-action flex-column align-items-center px-5"
                >
                    <div className="d-flex justify-content-between">
                        <h5>{video.name}</h5>
                        <div>
                            <small className="mr-5">
                                <Moment
                                  tz="America/Los_Angeles"
                                  format="YYYY-MM-DD HH:mm"
                                >
                                    {moment.utc(video.updated_at).format()}
                                </Moment>
                            </small>
                            <button
                                id={video.id}
                                className="btn btn-danger btn-sm"
                                onClick={this.handleDelete.bind(this)}
                            >
                              delete
                            </button>
                        </div>
                    </div>
                </a>
            )
          }.bind(this)
        );
        if (videoList.length === 0) {
          videoList.push(
            <div key={0} className="container text-center py-5">
                Empty
            </div>
          );
          isEmpty = true;
        }
        return (
          <div className="col-md-8">
              <div className="card">
                  <div className="card-header">Your Videos</div>
                  <div className="List-group" hidden={
                      this.props.status === status.FETCHING &&
                      isEmpty
                  }>
                      {videoList}
                  </div>
                  <div
                    className="card-body"
                    hidden={
                      this.props.status !== status.FETCHING ||
                      !isEmpty
                    }
                  >
                    <div className="row justify-content-center">
                      <i className="fa fa-spinner fa-spin"></i>
                    </div>
                  </div>
              </div>
          </div>
        );
    }
}

if (document.getElementById('VideoList')) {
    const element = document.getElementById('VideoList');
    const props = Object.assign({}, element.dataset);
    ReactDOM.render(<VideoList {...props} />, element);
}
