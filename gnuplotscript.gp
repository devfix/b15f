set margin 10,10
unset key
set grid
set title ''
set xlabel 'UDrain  [mV]'
set ylabel 'IDrain [mA]'
set xrange [0:5000]
set yrange [0:50]
set label at 2785,31 'UGS [Digit ] = 125' left
set label at 2663,28 'UGS [Digit ] = 150' left
set label at 2614,25 'UGS [Digit ] = 175' left
set label at 2541,18 'UGS [Digit ] = 200' left
set label at 2565,21 'UGS [Digit ] = 225' left
set label at 2468,13 'UGS [Digit ] = 250' left
set label at 2492,15 'UGS [Digit ] = 275' left
set label at 2443,11 'UGS [Digit ] = 300' left
set label at 2443,11 'UGS [Digit ] = 325' left
set label at 2394,8 'UGS [Digit ] = 350' left
set label at 2297,4 'UGS [Digit ] = 375' left
set label at 2297,4 'UGS [Digit ] = 400' left
set label at 2297,4 'UGS [Digit ] = 400' left
unset output 
set terminal qt
unset output
plot "/tmp/tempfile0" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 100' w l,"/tmp/tempfile1" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 125' w l,"/tmp/tempfile2" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 150' w l,"/tmp/tempfile3" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 175' w l,"/tmp/tempfile4" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 200' w l,"/tmp/tempfile5" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 225' w l,"/tmp/tempfile6" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 250' w l,"/tmp/tempfile7" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 275' w l,"/tmp/tempfile8" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 300' w l,"/tmp/tempfile9" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 325' w l,"/tmp/tempfile10" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 350' w l,"/tmp/tempfile11" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 375' w l,"/tmp/tempfile12" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 400' w l,"/tmp/tempfile13" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'UGS [Digit ] = 425' w l
