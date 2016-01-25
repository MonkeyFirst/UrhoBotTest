# UrhoBotTest

Testing and creation of a game robot called Spider.

## What's this?

An attempt to convert the project [MonkeyFirst/UrhoBotTest](https://github.com/MonkeyFirst/UrhoBotTest) to use
[Urho3D version 1.5](http://urho3d.github.io/releases/2015/11/11/urho3d-1.5-release.html).

## To build

    $ cd ~/
    $ git clone https://github.com/valera-rozuvan/UrhoBotTest.git
    $ cd UrhoBotTest
    $ git checkout migrate_to_urho3d_1_5
    $ mkdir build
    $ cd build
    $ cmake ../
    $ make

## To run

    $ cd ~/
    $ cd UrhoBotTest/build/bin
    $ ./MyExecutableName

## How it should look

See the [YouTube video](https://www.youtube.com/watch?v=yNIsJa_RqB8) of the original version.

## How it looks now (work in progress)

![screenshot](https://raw.githubusercontent.com/valera-rozuvan/stuff/master/images/strange-urho3d-behavior.png "screenshot")

## Errors while running the built project

    valera@valera-HP-ENVY-17-Notebook-PC:~/github.com/valera-rozuvan/UrhoBotTest/build/bin$ ./MyExecutableName
    [Mon Jan 25 18:11:10 2016] INFO: Opened log file /home/valera/.local/share/urho3d/logs/UrhoQuickStart.log
    [Mon Jan 25 18:11:10 2016] INFO: Created 3 worker threads
    [Mon Jan 25 18:11:10 2016] INFO: Added resource path /home/valera/github.com/valera-rozuvan/UrhoBotTest/build/bin/Data/
    [Mon Jan 25 18:11:10 2016] INFO: Added resource path /home/valera/github.com/valera-rozuvan/UrhoBotTest/build/bin/CoreData/
    [Mon Jan 25 18:11:10 2016] INFO: Set screen mode 1280x720 windowed
    [Mon Jan 25 18:11:10 2016] INFO: Initialized input
    [Mon Jan 25 18:11:10 2016] INFO: Initialized user interface
    [Mon Jan 25 18:11:10 2016] INFO: Initialized renderer
    [Mon Jan 25 18:11:10 2016] INFO: Set audio mode 44100 Hz stereo interpolated
    [Mon Jan 25 18:11:10 2016] INFO: Initialized engine
    [Mon Jan 25 18:11:10 2016] INFO: Loading scene from /home/valera/github.com/valera-rozuvan/UrhoBotTest/build/bin/Data/Scenes/MainScene.xml
    [Mon Jan 25 18:11:10 2016] ERROR: Failed to compile vertex shader Shadow(INSTANCED):
    0(130) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(131) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(132) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(133) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(134) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(135) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(136) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(137) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(138) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(139) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(141) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(142) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(143) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(181) : error C7616: global variable gl_ClipVertex is removed after version 140
    0(250) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    [Mon Jan 25 18:11:10 2016] ERROR: Failed to compile vertex shader Shadow(SKINNED):
    0(130) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(131) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(132) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(133) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(134) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(135) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(136) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(137) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(138) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(139) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(141) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(142) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(143) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(181) : error C7616: global variable gl_ClipVertex is removed after version 140
    0(250) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    [Mon Jan 25 18:11:10 2016] ERROR: Failed to compile vertex shader LitSolid(DIRLIGHT INSTANCED NORMALMAP PERPIXEL SHADOW):
    0(134) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(135) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(136) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(137) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(138) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(139) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(140) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(141) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(142) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(143) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(145) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(146) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(147) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(185) : error C7616: global variable gl_ClipVertex is removed after version 140
    0(595) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(596) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(600) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(601) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(604) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    [Mon Jan 25 18:11:10 2016] ERROR: Failed to compile pixel shader LitSolid(AMBIENT DIFFMAP DIRLIGHT NORMALMAP PERPIXEL SHADOW SPECMAP SPECULAR):
    0(446) : error C7616: global function shadow2DProj is removed after version 140
    0(598) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(599) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(603) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(604) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(607) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(751) : warning C7533: global variable gl_FragColor is deprecated after version 120
    [Mon Jan 25 18:11:10 2016] ERROR: Failed to compile vertex shader LitSolid(DIRLIGHT NORMALMAP PERPIXEL SHADOW):
    0(133) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(134) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(135) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(136) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(137) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(138) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(139) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(140) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(141) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(142) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(144) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(145) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(146) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(184) : error C7616: global variable gl_ClipVertex is removed after version 140
    0(594) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(595) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(599) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(600) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(603) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    [Mon Jan 25 18:11:10 2016] ERROR: Failed to compile vertex shader LitSolid(DIRLIGHT PERPIXEL SHADOW SKINNED):
    0(133) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(134) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(135) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(136) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(137) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(138) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(139) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(140) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(141) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(142) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(144) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(145) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(146) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(184) : error C7616: global variable gl_ClipVertex is removed after version 140
    0(597) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(599) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(600) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(603) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    [Mon Jan 25 18:11:10 2016] ERROR: Failed to compile pixel shader LitSolid(AMBIENT DIFFMAP DIRLIGHT PERPIXEL SHADOW SPECULAR):
    0(444) : error C7616: global function shadow2DProj is removed after version 140
    0(599) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(601) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(602) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(605) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(749) : warning C7533: global variable gl_FragColor is deprecated after version 120
    [Mon Jan 25 18:11:10 2016] ERROR: Failed to compile vertex shader Stencil():
    0(72) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(73) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(74) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(75) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(76) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(77) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(78) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(79) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(80) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(81) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(83) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(84) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(85) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(123) : error C7616: global variable gl_ClipVertex is removed after version 140
    [Mon Jan 25 18:11:10 2016] ERROR: Failed to compile vertex shader LitSolid(PERPIXEL POINTLIGHT SKINNED):
    0(132) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(133) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(134) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(135) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(136) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(137) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(138) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(139) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(140) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(141) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(143) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(144) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(145) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(183) : error C7616: global variable gl_ClipVertex is removed after version 140
    0(596) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(598) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(599) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(608) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    [Mon Jan 25 18:11:10 2016] ERROR: Failed to compile vertex shader Unlit(SKINNED):
    0(130) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(131) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(132) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(133) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(134) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(135) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(136) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(137) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(138) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(139) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(141) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(142) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(143) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(181) : error C7616: global variable gl_ClipVertex is removed after version 140
    0(327) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(328) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    [Mon Jan 25 18:11:11 2016] ERROR: Failed to compile vertex shader LitSolid(NORMALMAP PERPIXEL POINTLIGHT):
    0(132) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(133) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(134) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(135) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(136) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(137) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(138) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(139) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(140) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(141) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(143) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(144) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(145) : warning C7555: 'attribute' is deprecated, use 'in/out' instead
    0(183) : error C7616: global variable gl_ClipVertex is removed after version 140
    0(593) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(594) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(598) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(599) : warning C7555: 'varying' is deprecated, use 'in/out' instead
    0(608) : warning C7555: 'varying' is deprecated, use 'in/out' instead

## License

Pleasee see [LICENSE.txt](LICENSE.txt)
