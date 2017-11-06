#  PID Controller

## Your code should compile
It compiles correcly with cmake and make in a MacBook Pro with Xcode installed

## The PID procedure follows what was taught in the lessons

It is. optimization has been done manually. See anyway the **Comments** section.

## Describe the effect each of the P, I, D components had in your implementation.

**P** component is related to the precision but also to the capability of taking closed turns. You need a minimum value to be able to get the turns.

**D** component works as a way to "soft" the results of **P** component.


The P component is critical for reducing the CTE. Unfortunately it makes the system oscillate and diverge. The D component damps this effect and makes things more reasonable.

Finally the I component adjusts the steady state to CTE 0.

I have run different values for 1 turn computing :

    - CTE = Average CTE. Should go to 0
    - CTE2 = Average of CTE^2 squared. Gives idea of precision
    - Min CTE = Minim CTE value. Not very usefulAverage
    - Max CTE = Maximum of fabs(CTE). Gives idea of maximum oscillation



|P|I|D|CTE|CTE2|Min CTE|Max CTE|
|:----:|:----:|:----:|:--------:|:--------:|:--------:|:--------:|
|0.4|0|5.0|0.15|0.38|0.001|2.1381|
|0.4|0.01|5.0|0.00154111|0.358737|0.0002|1.943|
|0.4|0.01|10.0|.00159986|0.288663|0.0001|1.3966|
|0.4|0.01|20.0|.0017561|0.293024|0|1.1804|
|0.5|0.01|10.0|.00178629|0.274528|0|1.5889|
|0.6|0.01|10.0|0.00228343|0.372537|0.0002|2.4369|
|0.6|0.01|15.0|0.00536712|0.261957|0.0002|1.3778|
|0.6|0.01|20.0|0.000856665|0.254592|0.0002|1.2668
|0.6|0.01|25.0|0.00236477|0.285443|0.0001|1.7534|
|0.7|0.01|25.0|0.00199126|0.242594|0.0001|1.2002|
|0.8|0.01|25.0|0.000178531|0.265312|0|1.2009|
|0.8|0.01|30.0|0.00124614|0.243386|0|1.1472|
|0.8|0.02|35.0|0.000187815|0.219516|0|1.1314|
|1.0|0.02|45.0|0.00055162|0.188358|0|0.8625|
|1.5|0.02|34.0|0.000633164|0.167455|0.0001|1.0477|
|1.5|0.02|40.0|0.000654539|0.153528|0|0.8743|

First line is a conservative approach that works. It makes CTE (Average of CTE value) quite big, showing an offset.

Adding an I parameter CTE goes lower because the I term tries to remove the offset.

As you see incrementing the P term gives better accuracy (reduces CTE2) but you need a corresponding bigger D term to damp oscillations.

Anyway the behavior is a bit strange. First, augmenting P and D produce a "fast oscillation", more like a vibration which has the unfortunate effect of reducing the speed. This effect is related to the D term.

Finally the drive is not very smooth. When we are taking a curve the car goes straight and then makes a sharp turn, goes straight, sharp turn...

That is a clear consequence of two causes :

- The algorithm. When we have CTE = 0 and d CTE/dt is small the car goes straight but the road bends so CTE gets once again bigger.

- The timestep. As the timestep is bigger last effect is bigger. That was also very clear with the Neural Network project because when the computer was slower (ex. recording video)  we get worst results.

The clear solution to this problem is not to try to reduce CTE blindly but try to get a trajectory to a point in the future.
