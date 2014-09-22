function [] = new(w);

[a b] = imread(w);

[a] = binarize(a);

imwrite(w,a);
