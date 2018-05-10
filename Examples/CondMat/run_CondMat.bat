call ..\..\PATH.bat

..\..\LargeVis.exe -fea 0 -input CondMat_network.txt -output CondMat_vec2D.txt
python ../../plot.py -input CondMat_vec2D.txt -output CondMat_plot -range 35
pause