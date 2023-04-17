#define vtkRenderingContext2D_AUTOINIT 1(vtkRenderingContextOpenGL2)
#define vtkRenderingCore_AUTOINIT 3(vtkInteractionStyle,vtkRenderingFreeType,vtkRenderingOpenGL2)
#define vtkRenderingOpenGL2_AUTOINIT 1(vtkRenderingGL2PSOpenGL2)
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageSlice.h>
#include <vtkImageSliceMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main(int argc, char *argv[])
{
    // Create a 3D array of size 10x20x30
    const int width = 10;
    const int height = 20;
    const int depth = 30;
    float data[width][height][depth];

    // ... populate the data array with your own values ...

    // Choose which slice to display (in this case, the middle slice along the z-axis)
    const int sliceIndex = depth / 2;

    // Create a vtkImageData object and set its dimensions, spacing, and origin to match the data array
    vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();
    imageData->SetDimensions(width, height, 1);
    imageData->SetSpacing(1.0, 1.0, 1.0);
    imageData->SetOrigin(0.0, 0.0, 0.0);

    // Set the vtkImageData object's scalar type and allocate memory for its scalar data array
    // imageData->SetScalarTypeToFloat();
    // imageData->SetScalarType()
    imageData->AllocateScalars(VTK_FLOAT, 1);

    // Copy the slice you want to display from the data array into the scalar data array of the vtkImageData object
    float *imageDataPtr = static_cast<float *>(imageData->GetScalarPointer());
    float *dataPtr = &data[0][0][sliceIndex];
    const int numPixels = width * height;
    for (int i = 0; i < numPixels; i++)
    {
        *imageDataPtr++ = *dataPtr++;
    }

    // Create a vtkImageSlice object and set its vtkImageData input to your vtkImageData object
    vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
    vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
    imageSliceMapper->SetInputData(imageData);
    imageSlice->SetMapper(imageSliceMapper);

    // Create a vtkRenderer object and add the vtkImageSlice to it
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddViewProp(imageSlice);

    // Create a vtkRenderWindow object and add the vtkRenderer to it
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    // vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    // actor->SetMapper(mapper);
    // Add the actor to the renderer and set background color
    // renderer->AddActor(actor);
    renderer->SetBackground(1, 1, 1);

    // Start the rendering loop
    renderWindow->Render();
    interactor->Start();

    return 0;
}
