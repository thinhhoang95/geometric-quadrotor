accel = resample(accel, 0:0.02:30);
gyro = resample(gyro, 0:0.02:30);
feature = resample(feature, 0:0.02:30);
true_att = resample(true_att, 0:0.02:30);
true_pos = resample(true_pos, 0:0.02:30);