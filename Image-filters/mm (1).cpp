#include "Image_Class.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;
string filename;
void rotateImage(Image & pic , Image & rotated , int choice) {

    switch (choice) {
    case 1: {
        // Rotate 180 degrees clockwise
        for (int i = 0; i < pic.height; ++i) {
            for (int j = 0; j < pic.width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    rotated(pic.width - j - 1, pic.height - i - 1, k) = pic(j, i, k);
                }
            }
        }
        break;
    }
    case 2: {
        // Rotate 90 degrees clockwise
        for (int i = 0; i < pic.height; ++i) {
            for (int j = 0; j < pic.width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    rotated(pic.height - i - 1, j, k) = pic(j, i, k);
                }
            }
        }
        break;
    }
    case 3: {
        // Rotate 270 degrees clockwise
        for (int i = 0; i < pic.width; ++i) {
            for (int j = 0; j < pic.height; ++j) {
                rotated(j, pic.width - i - 1, 0) = pic(i, j, 0);
                rotated(j, pic.width - i - 1, 1) = pic(i, j, 1);
                rotated(j, pic.width - i - 1, 2) = pic(i, j, 2);
            }
        }
        break;
    }
    default:
        cout << "Invalid choice\n";
        return; // Exit function
    }
}

void purple_tint(Image& pic) {
    for (int i = 0; i < pic.width; i++) {
        for (int j = 0; j < pic.height; j++) {
            unsigned int red = pic(i, j, 0);
            unsigned int green = pic(i, j, 1);
            unsigned int blue = pic(i, j, 2);

            red = (4*red/5)+175/ 5;
            green = (4*green/5) + 45/ 5;
            blue = (4*blue/5) + 200/ 5;

            pic(i, j, 0) = red;
            pic(i, j, 1) = green;
            pic(i, j, 2) = blue;
        }
    }
}

void ApplyTVFilter(Image& pic) {
    srand(time(nullptr));

    for (int i = 0; i < pic.height; ++i) {
        if (i % 2 == 0) {
            int subtract_value = rand() % 11;
            for (int j = 0; j < pic.width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    unsigned int pixel_value = pic(j, i, k);
                    if (pixel_value >= subtract_value) {
                        pic(j, i, k) -= subtract_value;
                    } else {
                        pic(j, i, k) = 0;
                    }
                }
            }
        } else {
            int add_value = rand() % 11;
            for (int j = 0; j < pic.width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    unsigned int pixel_value = pic(j, i, k);
                    if (pixel_value + add_value <= 255) {
                        pic(j, i, k) += add_value;
                    } else {
                        pic(j, i, k) = 255;
                    }
                }
            }
        }
    }

    for (int i = 0; i < pic.height; ++i) {
        for (int j = 0; j < pic.width; ++j) {
            if (rand() % 10 == 0) {
                int r = rand() % 256;
                int g = rand() % 256;
                int b = rand() % 256;
                pic(j, i, 0) = (pic(j, i, 0) + r) / 2;
                pic(j, i, 1) = (pic(j, i, 1) + g) / 2;
                pic(j, i, 2) = (pic(j, i, 2) + b) / 2;
            }
        }
    }
}

//Mine
void merge(Image & image1 , Image & image2 , Image & image3)
{
        unsigned r1,r2,g1,g2,b1,b2,r3,g3,b3,avgr,avgg,avgb;
        for (int i = 0 ; i < image1.width ; i++ )
        {
            for (int j = 0 ; j < image1.height ; j++)
            {
                for (int k = 0 ; k < 3 ; k++)
                {
                   r1 = image1(i , j , 0);
                   g1 = image1(i , j , 1);
                   b1 = image1(i , j , 2);

                   r2 = image2(i , j , 0);
                   g2 = image2(i , j , 1);
                   b2 = image2(i , j , 2);

                   unsigned avgr = (r1 + r2) / 2;
                   unsigned avgg = (g1 + g2) / 2;
                   unsigned avgb = (b1 + b2) / 2;

                   image3.setPixel(i , j , 0 , avgr);
                   image3.setPixel(i , j , 1 , avgg);
                   image3.setPixel(i , j , 2 , avgb);
                }
            }
        }
}

//Mine
void infrared(Image & image){
    for (int i = 0 ; i < image.width ; i++)
    {
        for (int j = 0 ; j < image.height ; j++)
        {
            unsigned r = image(i , j , 0);
            unsigned g = image(i , j , 1);
            unsigned b = image(i , j , 2);
            for (int k = 0 ; k < 3 ; k++)
            {
                image.setPixel(i , j , 0 , 255);
                image.setPixel(i , j , 1 , 255 - g);
                image.setPixel(i , j , 2 , 255 - b);
            }

        }
    }
}

//Mine
void edge_detection(Image & image , Image & image2){
    for (int i = 0 ; i < image.width ; i++)
    {
        for (int j = 0 ; j < image.height ; j++)
        {
            unsigned average = 0;
            for (int k = 0 ; k < 3 ; k++)
                average += image(i , j , k);
            average /= 3;
            for (int k = 0 ; k < 3 ; k++)
            {
                image.setPixel(i , j , 0 , average);
                image.setPixel(i , j , 1 , average);
                image.setPixel(i , j , 2 , average);
            }
        }
    }

    for (int i = 1 ; i < image.width - 1 ; i++)
    {
        for (int j = 1 ; j < image.height - 1 ; j++)
        {
            for (int k = 0 ; k < 3 ; k++)
            {
                int x = image.getPixel(i + 1 , j , k) - image.getPixel(i - 1 , j , k);
                int y = image.getPixel(i , j + 1 , k) - image.getPixel(i , j - 1 , k);
                int gradient = abs(x) + abs(y);

                (gradient > 60)? image2.setPixel(i , j , k , 0) : image2.setPixel(i , j , k , 255);
            }
        }
    }
}

//Mine
void lighter (Image & pic){
    for (int i = 0 ; i < pic.width ; i++)
    {
        for (int j = 0 ; j < pic.height ; j++ )
        {
            unsigned r = pic(i , j , 0);
            unsigned g = pic(i , j , 1);
            unsigned b = pic(i , j , 2);
            for (int k = 0 ; k < 3 ; k++)
            {
                r *= 1.25;
                g *= 1.25;
                b *= 1.25;
                if (r > 255)
                    r = 255;
                if (g > 255)
                    g = 255;
                if (b > 255)
                    b = 255;

            }
            pic.setPixel(i , j , 0 , r);
            pic.setPixel(i , j , 1 , g);
            pic.setPixel(i , j , 2 , b);
        }
    }
}

void outfile(Image & image){
    cout<< "Please enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin.ignore();
    cin >> filename;
    image.saveImage(filename);
    system(filename.c_str());
}

bool saveorexit(Image &image, string input_filename){
     char op;
    cout << "do you want to save the picture or continue ?\n";
    cout << "to save the picture choose '1' to continue choose '2' \n";
    cin >> op;
        while (op != '1' && op != '2')
            {
            cout << "please choose a valid input\n";
            cin >> op;
            }
            if (op == '1')
            {
                return true;
            }
            else
            {
                return false;
            }

}

//Mine
void gray_scale( Image & pic){
    for (int i = 0; i < pic.width; i++)
    {
        for (int j = 0; j < pic.height; j++)
        {
            unsigned average = 0;
            for (int k = 0; k < 3; k++)
                average += pic(i, j, k);
            average /= 3;
            for (int k = 0; k < 3; k++)
            {
                pic.setPixel(i, j, 0, average);
                pic.setPixel(i, j, 1, average);
                pic.setPixel(i, j, 2, average);
            }
        }
    }
}

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

string InputFilePath() {
    string filename;
    while (true) {
        cout << "Enter the file path you want to include: ";
        getline(cin, filename);

        if (fileExists(filename)) {
            break;
        }
        else {
            cout << "Error: File does not exist. Please try again." << endl;
        }
    }
    return filename;
}

string OutputFilePath() {
    string filename;

    cout << "Enter the filename to save the filtered image (include extension):\n ";

    while (true) {
        getline(cin, filename);

        // Check if the filename is empty
        if (filename.empty()) {
            cout << "File cannot be empty." << endl;
            continue;
        }

        // Extract the extension
        size_t dotPosition = filename.find_last_of(".");
        if (dotPosition == string::npos) {
            cout << "Please include the file extension (e.g., '.png', '.jpg')" << endl;
            continue;
        }

        string extension = filename.substr(dotPosition);
        transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

        // Check if the extension is supported
        if (extension == ".jpg" || extension == ".jpeg" || extension == ".bmp" || extension == ".png") {
            // Check if the extension is already lowercase
            if (extension != filename.substr(dotPosition)) {
                filename.replace(dotPosition, extension.length(), extension);
            }
            break;
        }
        else {
            cout << "Unsupported file extension. Supported extensions are '.jpg', '.jpeg', '.bmp', '.png'" << endl;
        }
    }

    return filename;
}

void blackAwhite(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k); // Accumulate pixel values
            }
            avg /= 3; // Calculate average

            if (avg < 90) {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }
            else { // Otherwise, set to white
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            }
        }
    }

}

void invert(Image& image, Image& inverted) {
    string inside_op;
    cout << "invert : a) left to right  b) upside down" << endl;
    cin >> inside_op;
    if (inside_op == "a") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    // Calculate the corresponding pixel coordinates in the inverted image
                    int invertedX = image.width - 1 - i; // Reverse the x-coordinate


                    // Assign the pixel value from the original image to the inverted image
                    inverted(i, j, k) = image(invertedX, j, k);
                }
            }
        }
    }
    else if (inside_op == "b") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    // Calculate the corresponding pixel coordinates in the inverted image
                    int invertedY = image.height - 1 - j; // Reverse the x-coordinate


                    // Assign the pixel value from the original image to the inverted image
                    inverted(i, j, k) = image(i, invertedY, k);
                }
            }
        }
    }
    image = inverted;
}

void RGB(Image& pic) {
    for (int i = 0; i < pic.width; ++i) {
        for (int j = 0; j < pic.height; ++j) {
            unsigned int red = pic(i, j, 0);
            unsigned int green = pic(i, j, 1);
            unsigned int blue = pic(i, j, 2);

            pic(i, j, 0) = 255 - red;
            pic(i, j, 1) = 255 - green;
            pic(i, j, 2) = 255 - blue;
        }
    }
}

void resize(Image& image, Image& resized, int newWidth, int newHeight) {
    double widthRatio = (double)image.width / newWidth;
    double heightRatio = (double)image.height / newHeight;

    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Calculate the corresponding pixel coordinates in the original image
                int originalX = int(i * widthRatio);
                int originalY = int(j * heightRatio);

                // Assign the pixel value from the original image to the resized image
                resized(i, j, k) = image(originalX, originalY, k);
            }
        }
    }
}

void crop(Image& image, Image& cropped, int X, int Y, int cropWidth, int cropHeight) {

    for (int i = 0; i < cropWidth; ++i) {
        for (int j = 0; j < cropHeight; ++j) {
            for (int k = 0; k < image.channels; ++k) {

                int originalX = X + i;
                int originalY = Y + j;

                cropped(i, j, k) = image(originalX, originalY, k);
            }
        }
    }
}

//Mine
void darker (Image & pic){
    for (int i = 0 ; i < pic.width ; i++)
    {
        for (int j = 0 ; j < pic.height ; j++ )
        {
            unsigned r = pic(i , j , 0);
            unsigned g = pic(i , j , 1);
            unsigned b = pic(i , j , 2);
            for (int k = 0 ; k < 3 ; k++)
            {
                r *= 0.75;
                g *= 0.75;
                b *= 0.75;
                if (r < 0)
                    r = 0;
                if (g < 0)
                    g = 0;
                if (b < 0)
                    b = 0;

            }
            pic.setPixel(i , j , 0 , r);
            pic.setPixel(i , j , 1 , g);
            pic.setPixel(i , j , 2 , b);
        }
    }
}

void UserFrameColor(unsigned int& red, unsigned int& green, unsigned int& blue) {
    while (true) {
        cout << "Enter the RGB values for the frame color (0-255):\n";
        cout << "Red: ";
        cin >> red;
        if (red < 0 || red > 255) {
            cout << "Invalid input. Red value must be between 0 and 255. Please try again." << endl;
            continue;
        }

        cout << "Green: ";
        cin >> green;
        if (green < 0 || green > 255) {
            cout << "Invalid input. Green value must be between 0 and 255. Please try again." << endl;
            continue;
        }

        cout << "Blue: ";
        cin >> blue;
        if (blue < 0 || blue > 255) {
            cout << "Invalid input. Blue value must be between 0 and 255. Please try again." << endl;
            continue;
        }
        // If all inputs are within the valid range, break the loop
        break;
    }
}

void PlainFrame(Image& pic, unsigned int red, unsigned int green, unsigned int blue, int frameWidth) {
    // Add top and bottom frame
    for (int i = 0; i < pic.width; ++i) {
        for (int j = 0; j < frameWidth; ++j) {
            pic(i, j, 0) = red;
            pic(i, j, 1) = green;
            pic(i, j, 2) = blue;

            pic(i, pic.height - 1 - j, 0) = red;
            pic(i, pic.height - 1 - j, 1) = green;
            pic(i, pic.height - 1 - j, 2) = blue;
        }
    }

    // Add left and right frame
    for (int j = 0; j < pic.height; ++j) {
        for (int i = 0; i < frameWidth; ++i) {
            pic(i, j, 0) = red;
            pic(i, j, 1) = green;
            pic(i, j, 2) = blue;

            pic(pic.width - 1 - i, j, 0) = red;
            pic(pic.width - 1 - i, j, 1) = green;
            pic(pic.width - 1 - i, j, 2) = blue;
        }
    }
}

void DecorativeFrame(Image& pic, unsigned int red, unsigned int green, unsigned int blue) {
    int patternFrequency = 40; // Adjust this value for the frequency of the pattern
    // Calculate frame width as a percentage of image dimensions
    int frameWidth = min(pic.width, pic.height) * 0.05; // Adjust the percentage as needed (5%)

    // Apply the pattern to the top and bottom frames
    for (int i = 0; i < pic.width; ++i) {
        for (int j = 0; j < frameWidth; ++j) {
            // Calculate the pattern based on the frequency
            if ((i / patternFrequency + j / patternFrequency) % 2 == 0) {
                // Apply the user-selected color for the pattern
                pic(i, j, 0) = red;
                pic(i, j, 1) = green;
                pic(i, j, 2) = blue;

                // Apply the same pattern to the bottom frame
                pic(i, pic.height - 1 - j, 0) = red;
                pic(i, pic.height - 1 - j, 1) = green;
                pic(i, pic.height - 1 - j, 2) = blue;
            } else {
                // Apply white for the background
                pic(i, j, 0) = 255; // White
                pic(i, j, 1) = 255; // White
                pic(i, j, 2) = 255; // White

                // Apply the same pattern to the bottom frame
                pic(i, pic.height - 1 - j, 0) = 255; // White
                pic(i, pic.height - 1 - j, 1) = 255; // White
                pic(i, pic.height - 1 - j, 2) = 255; // White
            }
        }
    }

    // Apply the pattern to the left and right frames
    for (int j = 0; j < pic.height; ++j) {
        for (int i = 0; i < frameWidth; ++i) {
            // Calculate the pattern based on the frequency
            if ((i / patternFrequency + j / patternFrequency) % 2 == 0) {
                // Apply the user-selected color for the pattern
                pic(i, j, 0) = red;
                pic(i, j, 1) = green;
                pic(i, j, 2) = blue;

                // Apply the same pattern to the right frame
                pic(pic.width - 1 - i, j, 0) = red;
                pic(pic.width - 1 - i, j, 1) = green;
                pic(pic.width - 1 - i, j, 2) = blue;
            } else {
                // Apply white for the background
                pic(i, j, 0) = 255; // White
                pic(i, j, 1) = 255; // White
                pic(i, j, 2) = 255; // White

                // Apply the same pattern to the right frame
                pic(pic.width - 1 - i, j, 0) = 255; // White
                pic(pic.width - 1 - i, j, 1) = 255; // White
                pic(pic.width - 1 - i, j, 2) = 255; // White
            }
        }
    }
}

vector<vector<vector<long long>>> calculatePrefixSum(Image& pic) {
    vector<vector<vector<long long>>> prefixSum(pic.width, vector<vector<long long>>(pic.height, vector<long long>(3)));

    for (long long i = 1; i < pic.width; ++i) {
        prefixSum[i][0][0] = pic(i, 0, 0) + prefixSum[i-1][0][0];
        prefixSum[i][0][1] = pic(i, 0, 1) + prefixSum[i-1][0][1];
        prefixSum[i][0][2] = pic(i, 0, 2) + prefixSum[i-1][0][2];
    }
    for (long long j = 1; j < pic.height; ++j) {
        prefixSum[0][j][0] = pic(0, j, 0) + prefixSum[0][j-1][0];
        prefixSum[0][j][1] = pic(0, j, 1) + prefixSum[0][j-1][1];
        prefixSum[0][j][2] = pic(0, j, 2) + prefixSum[0][j-1][2];
    }

    for (int channel = 0; channel < 3; ++channel) {
        for (int i = 1; i < pic.width; ++i) {
            for (int j = 1; j < pic.height; ++j) {
                prefixSum[i][j][channel] = pic(i, j, channel) +
                                           prefixSum[i - 1][j][channel] +
                                           prefixSum[i][j - 1][channel] -
                                           prefixSum[i - 1][j - 1][channel];
            }
        }
    }
    return prefixSum;
}

Image BlurFilter(Image& pic, int radius) {
    vector<vector<vector<long long>>> prefixSum = calculatePrefixSum(pic);
    int count = (radius * 2 + 1) * (radius * 2 + 1);
    Image temp(pic.width, pic.height);
    for (int i = 0; i < pic.width; ++i) {
        for (int j = 0; j < pic.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                long long x1, x2, y1, y2;
                (i - radius - 1 < 0) ? x1 = 0 : x1 = i - radius - 1;
                (j - radius - 1 < 0) ? y1 = 0 : y1 = j - radius - 1;
                (i + radius >= pic.width-1) ? x2 = pic.width-1 : x2 = i + radius;
                (j + radius >= pic.height-1) ? y2 = pic.height-1 : y2 = j + radius;

                long long Sum = prefixSum[x2][y2][k] - prefixSum[x1][y2][k] - prefixSum[x2][y1][k] + prefixSum[x1][y1][k];
                temp(i, j, k) = Sum / count;
            }
        }
    }
    return temp;
}


int main() {
    string filename;
    while(true){
    string input_filename = InputFilePath();
    string op;
    while (true) {
        Image input_image(input_filename);
        cout << "what filter would you like to use on your picture:\n1)black and white\n2)inverter\n3)inverse colors\n4)image rotate\n5)gray scale\n6)crop\n7)resize\n8)edge detector\n9)make lighter\n10)make darker\n11)border\n12)merge two pictures\n13)blur\n14)exit\n15)infrared\n16)purple tint\n17)tv effect" << endl;
        cin >> op;
        while (op != "1" && op != "2" && op != "3" && op != "4" && op != "5" && op != "6" && op != "7" && op != "8" && op != "9" && op != "10" && op != "11" && op != "12" && op != "13" && op != "14" && op != "15" && op != "16" && op != "17" )
        {
            cout << "please choose a valid input \n";
            cin >> op;
        }
        if (op == "14")
        {
            return 0;
        }

        else if (op == "1")
        {
            blackAwhite(input_image);
        }

        else if (op == "2")
        {
            Image inverted_output;
            inverted_output.loadNewImage(input_filename);
            invert(input_image, inverted_output);
            if (saveorexit(inverted_output, input_filename)){
                outfile(inverted_output);
                break;
            }
            else{
                inverted_output.saveImage(input_filename);
                system(input_filename.c_str());
                continue;
            }
    }

        else if (op == "3")
        {
            RGB(input_image);
        }

        else if (op == "4")
        {
            int choice;
            cout << "choose the rotation you want \n1)180\n2)90\n3)270"<<endl;
            cin >> choice;
            if (choice == 1)
            {
                Image rotated(input_image.width , input_image.height);
                rotateImage(input_image , rotated , 1);
                if (saveorexit(rotated, input_filename))
                {
                    outfile(rotated);
                    break;
                }
                else
                {
                    rotated.saveImage(input_filename);
                    system(input_filename.c_str());
                    continue;
                }
            }
            else if (choice == 2)
            {
                Image rotated(input_image.height , input_image.width);
                rotateImage(input_image , rotated , 2);
                if (saveorexit(rotated, input_filename))
                {
                    outfile(rotated);
                    break;
                }
                else
                {
                    rotated.saveImage(input_filename);
                    system(input_filename.c_str());
                    continue;
                }
            }
            else
            {
                Image rotated(input_image.height , input_image.width);
                rotateImage(input_image , rotated , 3);
                if (saveorexit(rotated, input_filename))
                {
                    outfile(rotated);
                    break;
                }
                else
                {
                    rotated.saveImage(input_filename);
                    system(input_filename.c_str());
                    continue;
                }
            }
        }

        else if (op == "5")
        {
            gray_scale( input_image);
        }

         else if (op == "6")
        {
            int hig, wid, startx, starty;
            cout<< "enter new width: "<<endl;
            cin>>wid;
            cout<<"enter new height: "<<endl;
            cin>>hig;
            cout<< "enter first pixel x: "<<endl;
            cin>>startx;
            cout<< "enter first pixel y: "<<endl;
            cin>>starty;
            while (startx < 0 || starty < 0 || startx + wid > input_image.width || starty + hig > input_image.height) {
                cout << "Error: Crop dimensions are invalid, please enter again.\n======================" <<endl;
                cout<< "enter new width: "<<endl;
                cin>>wid;
                cout<<"enter new height: "<<endl;
                cin>>hig;
                cout<< "enter first pixel x: "<<endl;
                cin>>startx;
                cout<< "enter first pixel y: "<<endl;
                cin>>starty;

            }
            Image cropped_output(wid, hig);
            crop(input_image, cropped_output, startx, starty, wid, hig);
            if (saveorexit(cropped_output, input_filename)){
                outfile(cropped_output);
                break;
            }
            else{
                cropped_output.saveImage(input_filename);
                system(input_filename.c_str());
                continue;
            }

        }

        else if (op == "7")
        {
            int wid2, hig2;
            cout<< "enter new width: "<<endl;
            cin>>wid2;
            cout<<"\n"<<"enter new height: "<<endl;
            cin>>hig2;
            Image resized_output(wid2, hig2);
            resize(input_image, resized_output, wid2, hig2);
            if (saveorexit(resized_output, input_filename)){
                outfile(resized_output);
                break;
            }
            else{
                resized_output.saveImage(input_filename);
                system(input_filename.c_str());
                continue;
            }

        }

        else if (op == "8")
        {
            Image image2(input_image.width , input_image.height);
            edge_detection(input_image , image2 );
            if (saveorexit(image2, input_filename)){
                outfile(image2);
                break;
            }
            else{
                image2.saveImage(input_filename);
                system(input_filename.c_str());
                continue;
            }

        }

        else if (op == "9")
        {
            lighter(input_image);

        }

        else if (op == "10")
        {
            darker(input_image);
        }

        else if (op == "11")
        {
            // Get frame color from user
            unsigned int red, green, blue;
            UserFrameColor(red, green, blue);

            // Choose frame type
            int frameChoice;
            // Loop until a valid choice (1 or 2) is made
            while (true) {
                cout << "Choose the frame type:\n";
                cout << "1. Plain\n";
                cout << "2. Decorative\n";
                cout << "Enter your choice: ";
                cin >> frameChoice;

                if (frameChoice == 1) {
                    // Calculate frame width as a percentage of image dimensions
                    int frameWidth = min(input_image.width, input_image.height) * 0.05; // Adjust the percentage as needed (e.g., 0.05 for 5%)
                    PlainFrame(input_image, red, green, blue, frameWidth);
                    break; // Exit the loop if a valid choice is made
                } else if (frameChoice == 2) {
                    // Apply the decorative frame
                    DecorativeFrame(input_image, red, green, blue);
                    break; // Exit the loop if a valid choice is made
                } else {
                    cout << "Invalid choice. Please choose again." << endl;
                }
            }

        }

        else if (op == "12")
        {
            string filename2;
            cout << "enter the second image name to merge : " << endl;
            cin >> filename2;
            Image image2(filename2);
            int A1 = input_image.width * input_image.height;
            int A2 = image2.width * image2.height;
            if (A1 > A2)
            {
                Image resized_output(input_image.width , input_image.height);
                resize (image2 , resized_output ,input_image.width , input_image.height);
                Image image3(input_image.width , input_image.height);
                merge(input_image , resized_output , image3);
                if (saveorexit(image3, input_filename))
                {
                    outfile(image3);
                    break;
                }
                else
                {
                    image3.saveImage(input_filename);
                    system(input_filename.c_str());
                    continue;
                }

            }
            else if (A2 > A1)
            {
                Image resized_output(image2.width , image2.height);
                resize (input_image , resized_output ,image2.width , image2.height);
                Image image3(image2.width , image2.height);
                merge(resized_output , image2 , image3);
                if (saveorexit(image3, input_filename))
                {
                    outfile(image3);
                    break;
                }
                else
                {
                    image3.saveImage(input_filename);
                    system(input_filename.c_str());
                    continue;
                }
            }
            else
            {
                Image image3(input_image.width , input_image.height);
                merge(input_image , image2 , image3);
                if (saveorexit(image3, input_filename))
                {
                    outfile(image3);
                    break;
                }
                else
                {
                    image3.saveImage(input_filename);
                    system(input_filename.c_str());
                    continue;
                }
            }
        }

        else if (op == "13")
        {
            int radius ;
            cout<<"Please enter the percentage of the blur you want (10 : 30): \n";
            cin>>radius;
            while (radius < 10 || radius > 30) {
                cout << "Radius better to be between 10 and 30." << endl;
                cout << "Please enter the percentage of the blur you want (15 : 30): ";
                cin >> radius;
            }
            input_image = BlurFilter(input_image, radius);

        }
        else if (op == "15")
        {
            infrared(input_image);
        }
        else if (op == "16")
        {
            purple_tint(input_image);
        }
        else if (op == "17")
        {
            ApplyTVFilter(input_image);
        }

        if (saveorexit(input_image, input_filename))
        {
            outfile(input_image);
            break;
        }
        else
        {
            input_image.saveImage(input_filename);
            system(input_filename.c_str());
            continue;
        }
    }
        cout << "do you want to exit or continue editing ?\n";
        cout << "to exit compeletely choose '1' to edit a picture choose '2' \n";
        cin >> op;
        while (op != "1" && op != "2")
        {
            cout << "please choose a valid input\n";
            cin >> op;
        }
        if (op == "1")
        {
            break;
        }
        else {
            continue;
        }
    }
    return 0;
}
