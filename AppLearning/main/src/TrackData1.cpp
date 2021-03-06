
#include "AppLearning/main/inc/TrackData1.hpp"
#include "Misc/main/inc/Vector2D.hpp"

TrackData1::TrackData1()
    : ::TrackData("AppLearning/main/inc/TrackData1") {
    points.push_back(new Vector2D(240.0, 166.0));
    points.push_back(new Vector2D(198.00, 174.01));
    points.push_back(new Vector2D(157.0, 185.0));
    points.push_back(new Vector2D(124.02, 205.39));
    points.push_back(new Vector2D(95.0, 231.0));
    points.push_back(new Vector2D(71.31, 268.36));
    points.push_back(new Vector2D(54.0, 309.0));
    points.push_back(new Vector2D(52.17, 346.29));
    points.push_back(new Vector2D(55.0, 384.0));
    points.push_back(new Vector2D(58.21, 424.04));
    points.push_back(new Vector2D(66.0, 463.0));
    points.push_back(new Vector2D(85.99, 489.38));
    points.push_back(new Vector2D(109.0, 514.0));
    points.push_back(new Vector2D(139.08, 549.27));
    points.push_back(new Vector2D(165.0, 587.0));
    points.push_back(new Vector2D(175.44, 636.84));
    points.push_back(new Vector2D(181.0, 688.0));
    points.push_back(new Vector2D(184.68, 735.14));
    points.push_back(new Vector2D(190.0, 782.0));
    points.push_back(new Vector2D(199.36, 809.94));
    points.push_back(new Vector2D(214.0, 835.0));
    points.push_back(new Vector2D(242.25, 854.15));
    points.push_back(new Vector2D(274.0, 867.0));
    points.push_back(new Vector2D(325.28, 871.58));
    points.push_back(new Vector2D(377.0, 871.0));
    points.push_back(new Vector2D(431.29, 866.93));
    points.push_back(new Vector2D(484.0, 856.0));
    points.push_back(new Vector2D(516.41, 831.10));
    points.push_back(new Vector2D(544.0, 800.0));
    points.push_back(new Vector2D(562.51, 768.06));
    points.push_back(new Vector2D(577.0, 734.0));
    points.push_back(new Vector2D(588.71, 687.38));
    points.push_back(new Vector2D(597.0, 640.0));
    points.push_back(new Vector2D(600.71, 583.56));
    points.push_back(new Vector2D(603.0, 527.0));
    points.push_back(new Vector2D(605.38, 487.49));
    points.push_back(new Vector2D(608.0, 448.0));
    points.push_back(new Vector2D(608.80, 404.81));
    points.push_back(new Vector2D(615.0, 363.0));
    points.push_back(new Vector2D(637.64, 336.52));
    points.push_back(new Vector2D(667.0, 317.0));
    points.push_back(new Vector2D(706.44, 309.92));
    points.push_back(new Vector2D(747.0, 309.0));
    points.push_back(new Vector2D(794.36, 311.06));
    points.push_back(new Vector2D(839.0, 322.0));
    points.push_back(new Vector2D(862.63, 355.20));
    points.push_back(new Vector2D(880.0, 394.0));
    points.push_back(new Vector2D(895.36, 429.14));
    points.push_back(new Vector2D(909.0, 465.0));
    points.push_back(new Vector2D(920.41, 517.20));
    points.push_back(new Vector2D(938.0, 566.0));
    points.push_back(new Vector2D(980.23, 594.21));
    points.push_back(new Vector2D(1029.0, 612.0));
    points.push_back(new Vector2D(1077.57, 616.79));
    points.push_back(new Vector2D(1125.0, 610.0));
    points.push_back(new Vector2D(1165.34, 576.82));
    points.push_back(new Vector2D(1198.0, 535.0));
    points.push_back(new Vector2D(1212.72, 495.13));
    points.push_back(new Vector2D(1220.0, 453.0));
    points.push_back(new Vector2D(1219.81, 371.96));
    points.push_back(new Vector2D(1210.0, 292.0));
    points.push_back(new Vector2D(1182.90, 232.75));
    points.push_back(new Vector2D(1144.0, 181.0));
    points.push_back(new Vector2D(1091.52, 155.15));
    points.push_back(new Vector2D(1034.0, 140.0));
    points.push_back(new Vector2D(971.66, 138.28));
    points.push_back(new Vector2D(909.0, 141.0));
    points.push_back(new Vector2D(828.00, 143.61));
    points.push_back(new Vector2D(747.0, 146.0));
    points.push_back(new Vector2D(677.49, 145.49));
    points.push_back(new Vector2D(608.0, 145.0));
    points.push_back(new Vector2D(532.98, 147.03));
    points.push_back(new Vector2D(458.0, 150.0));
    points.push_back(new Vector2D(393.47, 153.65));
    points.push_back(new Vector2D(329.0, 158.0));
    points.push_back(new Vector2D(293.48, 161.34));
    points.push_back(new Vector2D(258.0, 165.0));

    translate(-1, 70);
    computePointsAndPerpList();
}
