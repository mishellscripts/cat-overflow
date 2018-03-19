import React, { Component } from 'react';
import ReactDOM from 'react-dom';
import moment from 'moment';
import Moment from 'react-moment';
import 'moment-timezone';

export default class VideoList extends Component {
    render() {
        var videoList = [];
        this.props.videos.forEach(function(video) {
            videoList.push(
                <a
                  key={video.id}
                  href={"/originalVideos/" + video.id}
                  className="list-group-item list-group-item-action flex-column align-items-center px-5"
                >
                    <div className="d-flex w-100 justify-content-between">
                        <h5>{video.name}</h5>
                        <small>
                            <Moment
                              tz="America/Los_Angeles"
                              format="YYYY-MM-DD HH:mm"
                            >
                                {moment.utc(video.updated_at).format()}
                            </Moment>
                        </small>
                    </div>
                </a>
            )
          }
        );
        return (
          <div className="col-md-8">
              <div className="card">
                  <div className="card-header">Your Videos</div>
                  <div className="List-group">
                      {videoList}
                  </div>
                  <div className="card-body" hidden={videoList.length !== 0}>
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
