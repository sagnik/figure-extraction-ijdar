function [a]=bin_pgm(im);

%make predominant number white (0), remainder black (1) i.e. mark any feature with black and else (background) white.
b=imread(im);
keyboard;
  
imwrite(b,'sample_gif.gif');



