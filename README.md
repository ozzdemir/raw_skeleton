# raw_skeleton
Ros package that listens tf data published by openni2_tracker by futureneer (or skeleton_tracker by chaos84)
+ First run
```
roslaunch raw_skeleton raw_skeleton.launch
```
+ Wait for user to be tracked and then call following with relevant parameters (such as tracked user id, tracking enable)
```
rosservice call /raw_skeleton/update_user_id "user_id: '1'
track_user: true" 
```
+ When user wants to quit or an another one came up, call the service with track_user: false
```
rosservice call /raw_skeleton/update_user_id "user_id: '1'
track_user: false" 
```
