set xlabel "Bits per Pixel"
set ylabel "PSNR"
set key left top

set style data linespoints
set grid

set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5   # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 1.5   # --- red

plot "test1.txt" using 1:2 title 'Single Block'     ls 1, \
     "test1.txt" using 3:4 title 'Matching Pursuit' ls 2