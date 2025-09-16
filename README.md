# Parallel Image Processing 
A terminal based application applying color filters, edge detection, and gaussian blur using parallel algorithms with OpenMP.

![app_preview](https://github.com/user-attachments/assets/e505984b-2784-45c3-8970-4b3f2ea22e33)

***
- Incorporates an image processing library, OpenCV for matrix construction, pixel channel access, loading, saving and displaying the images.
- Applies parallel algorithm with OpenMP directives: parallel for collapse, num_threads specification, and single parallel region.

## Method:
- Pixel Channel Manipulation - setting opposing channels to 0 or 255 to intensify for the selected color
- Grayscale - Using a single channel and calculating the luma of each pixel with sRGB values
- Gaussian Blur Theory - Using a Gaussian kernel of 7 and sigma of 7 for blur intensity followed by calculating the weight of each neighbioring pixel
- Edge Detection - Using Difference of Gaussians Theory with a sigma of 2 and 9, a kernel of 7 and threshold intensity of 4

***
## Filters Available
### Colorize
<img width="961" height="540" alt="image" src="https://github.com/user-attachments/assets/934de411-5397-4cc0-b5e2-a3408f065dc2" />

### Blur
<img width="959" height="542" alt="image" src="https://github.com/user-attachments/assets/fbef1e9f-1097-41be-9a73-591863000d5e" />

### Edge Detection
<img width="963" height="543" alt="image" src="https://github.com/user-attachments/assets/f81b8710-4471-4fb0-86a8-e3971c7ca614" />


***
## Perfomance
### Colorize - Primary
<img width="728" height="432" alt="image" src="https://github.com/user-attachments/assets/989ec6ac-6757-4c89-9581-3fc9449559a8" />

### Colorize - Secondary
<img width="716" height="482" alt="image" src="https://github.com/user-attachments/assets/64bd6166-09cb-4da5-87a8-5ccd856893db" />

### Colorize - Grayscale
<img width="718" height="479" alt="image" src="https://github.com/user-attachments/assets/dc3e3cc1-1a8f-4745-96e7-0cde82e6744f" />

### Colorize - Complimentary Inverse
<img width="727" height="445" alt="image" src="https://github.com/user-attachments/assets/9c526506-f2e0-41ed-bac1-39a09e6967b2" />

### Blur - Gaussian Blur
<img width="727" height="442" alt="image" src="https://github.com/user-attachments/assets/79fa3d1a-dbc6-4381-900c-7bdfbf76931f" />

### Edge Detection - Difference of Gaussians
<img width="719" height="437" alt="image" src="https://github.com/user-attachments/assets/24bfb2aa-b639-4aef-9291-0f0c17b0094b" />

