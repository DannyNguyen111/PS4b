# PS4b
Aniplayer

In PS4b, I enhanced the Static Animation Player by implementing tweened animation playback using SFML, enabling smooth transitions between keyframes over time. The AniPlayer tracks elapsed time with an internal clock and calculates an interpolation factor t to blend properties like position, rotation, and color between the current and next keyframes using linear interpolation. Positions and rotations are tweened by interpolating their numerical values, while colors are smoothly blended by linearly interpolating each RGBA component separately. During each frame update, these interpolated values update the SFML shapes before drawing, producing seamless animation playback. The system manages timing by determining the relevant keyframes based on elapsed time and loops or holds the animation as needed, maintaining a modular design that supports flexible component hierarchies and future extension of tweenable properties.

<img width="1214" height="864" alt="screenshot" src="https://github.com/user-attachments/assets/06a6a78f-ba04-4993-80f6-bd09103f57f1" />
