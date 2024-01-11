/*
LPDIRECT3D9 d3d; //the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev; //the pointer to the device classs
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL; //vertex buffer pointer
LPDIRECT3DINDEXBUFFER9 i_buffer = NULL; //vertex buffer pointer


void initD3D(HWND hWnd); //sets up and inintializes Direct3D
void render_frame(void); //Renders a single frame
void cleanD3D(void); //closes Direct3D and releases memory



struct CUSTOMVERTEX
{
    FLOAT x, y, z;
    DWORD color;
};

void init_graphics(void)
{

    CUSTOMVERTEX OurVertices[] =
    {
        { -1.0f,  1.0f, -2.0f, D3DCOLOR_XRGB(0, 255, 0),},
        { -1.0f,  4.0f, -2.0f, D3DCOLOR_XRGB(0, 0,255),},
        { 0.0f,   4.0f, -2.0f, D3DCOLOR_XRGB(255,0, 255),},
        { 0.0f,   1.0f, -2.0f, D3DCOLOR_XRGB(0, 255, 255),},
        { 1.5f,   1.0f, -2.0f, D3DCOLOR_XRGB(255, 0, 0),},
        { 1.5f,   0.0f, -2.0f, D3DCOLOR_XRGB(255, 0, 0),},
        { 0.0f,   0.0f, -2.0f, D3DCOLOR_XRGB(255, 0, 0),},
        { -1.0f,  0.0f, -2.0f, D3DCOLOR_XRGB(0, 255, 0),},

    };

    d3ddev->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX), 0, CUSTOMFVF, D3DPOOL_MANAGED, &v_buffer, NULL); //create vertex buffer

    VOID* pVoid; //void pointer to lock vertex buffer

    v_buffer->Lock(0, 0, (void**)&pVoid, 0); //lock the vertex buffer


    memcpy(pVoid, OurVertices, sizeof(OurVertices)); //copy the vertices to the vertex buffer

    v_buffer->Unlock(); //unlock the vertex buffer, we no longer need it anymore

    short indices[] =
    {
        7,1,2,
        7,2,6,
        6,3,4,
        6,4,5



    };
    d3ddev->CreateIndexBuffer(24 * sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &i_buffer, NULL);

    void* pVoid2;

    i_buffer->Lock(0, 0, (void**)&pVoid2, 0);
    memcpy(pVoid2, indices, sizeof(indices));
    i_buffer->Unlock();

    /*

    d3ddev->CreateIndexBuffer(36 * sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &i_buffer, NULL);
    i_buffer->Lock(0, 0, (void**)pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    i_buffer->Unlock();
}




void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION); //create the Direct3D interface

    D3DPRESENT_PARAMETERS d3dpp; //create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp)); //clear out the struct for use
    d3dpp.Windowed = TRUE; //windowed mode
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //discarding old frames in the swap chain
    d3dpp.hDeviceWindow = hWnd; //setting device window to our window handle
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8; //set the back buffer format to 32 bit
    d3dpp.BackBufferWidth = SCREEN_WIDTH; //set the width of the buffer
    d3dpp.BackBufferHeight = SCREEN_HEIGHT; //set the height of the buffer
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


    d3d->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &d3ddev); // create d3d device


    init_graphics();
    d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
    d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);

}

void render_frame(void)
{

    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    d3ddev->BeginScene(); //begins 3d scene

    d3ddev->SetFVF(CUSTOMFVF); //select the vertex format we are using

    D3DXMATRIX matView;

    D3DXVECTOR3 v1 = { 0.0f, 0.0f, 30.0f };
    D3DXVECTOR3 v2 = { 0.0f, 0.0f, 0.0f };
    D3DXVECTOR3 v3 = { 0.0f, 1.0f,0.0f };


    D3DXMatrixLookAtLH(&matView, &v1, &v2, &v3);
    d3ddev->SetTransform(D3DTS_VIEW, &matView);



    D3DXMATRIX matProj;

    D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(30), (FLOAT)SCREEN_HEIGHT / (FLOAT)SCREEN_HEIGHT, 1.0f, 100.0f);

    d3ddev->SetTransform(D3DTS_PROJECTION, &matProj);


    D3DXMATRIX matRotateY;
    static float index = 0.0f; index += 0.01f;
    D3DXMatrixRotationY(&matRotateY, index);
    d3ddev->SetTransform(D3DTS_WORLD, &matRotateY);


    d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX)); //select the vertex buffer to display
    d3ddev->SetIndices(i_buffer);
    d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 8);


    d3ddev->EndScene(); //ends 3d scene

    d3ddev->Present(NULL, NULL, NULL, NULL); //displays the created frame

}


void cleanD3D(void)
{
    v_buffer->Release(); //close and release the vertex buffer
    //i_buffer->Release();
    d3ddev->Release(); //close and release the 3D device
    d3d->Release(); //close and release Direct3D
}

*/



/*
* OLD CODE
*
*
   //the handle for the window
   HWND hWnd;

   // this struct holds information for the window class
   WNDCLASSEX wc;

   // clear out the window class for use
   ZeroMemory(&wc, sizeof(WNDCLASSEX));

   // fill in the struct with the needed information
   wc.cbSize = sizeof(WNDCLASSEX);
   wc.style = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc = WindowProc;
   wc.hInstance = hInstance;
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
   wc.lpszClassName = L"WindowClass1";

   // register the window class
   RegisterClassEx(&wc);


   // create the window and use the result as the handle
   hWnd = CreateWindowEx(NULL,
       L"WindowClass1",    // name of the window class
       L"Our First Windowed Program",   // title of the window
       WS_OVERLAPPEDWINDOW,    // window style
       300,    // x-position of the window
       300,    // y-position of the window
       1280,    // width of the window
       720,    // height of the window
       NULL,    // we have no parent window, NULL
       NULL,    // we aren't using menus, NULL
       hInstance,    // application handle
       NULL);    // used with multiple windows, NULL


*/

/*
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch (message)
    {
        // this message is read when the window is closed
    case WM_DESTROY:
    {
        // close the application entirely
        PostQuitMessage(0);
        return 0;
    } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}
*/

/*
  m_hWnd = CreateWindowEx(NULL,
      name,    // name of the window class
      L"Our First Windowed Program",   // title of the window
      WS_OVERLAPPEDWINDOW,    // window style
      900,    // x-position of the window
      400,    // y-position of the window
      w,    // width of the window
      h,    // height of the window
      NULL,    // we have no parent window, NULL
      NULL,    // we aren't using menus, NULL
      hInstance,    // application handle
      NULL);    // used with multiple windows, NULL
      */