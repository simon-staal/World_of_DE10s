using UnityEngine;
using System.Collections;
using System;
using System.IO;
using System.Net.Sockets;
using System.Threading.Tasks;

using System.Threading;
using System.Net;

public class client : MonoBehaviour
{
    int i = 60;
    internal Boolean socketReady = false;
    TcpClient mySocket;
    NetworkStream theStream;
    StreamWriter theWriter;
    StreamReader theReader;
    String Host = "52.56.73.213";
    Int32 Port = 8080;
    public bool activated = false;
    // Start is called before the first frame update
    private bool mRunning;
    public Thread mThread;
    [SerializeField] runnerCharacterController instance;
    [SerializeField] characterController instance2;
    void Start()
    {

        mRunning = true;
        ThreadStart ts = new ThreadStart(Receive);
        mThread = new Thread(ts);
        mThread.Start();
        print("Thread done...");
 

    }

    private void Receive()
    {
        setupSocket();
        String s = readSocket();
        String send = "U";
        writeSocket(send);
        while (mRunning)
        {
            s = readSocket();  
            Debug.Log(s);
            instance.x = s;
            instance2.x = s;
        }
    }


    /// <summary> 	
    /// Setup socket connection. 	
    /// </summary> 	
    public void setupSocket()
    {
        try
        {
            mySocket = new TcpClient(Host, Port);
            theStream = mySocket.GetStream();
            theWriter = new StreamWriter(theStream);
            theReader = new StreamReader(theStream);
            socketReady = true;
        }
        catch (Exception e)
        {
            Debug.Log("Socket error: " + e);
        }
    }
    public void writeSocket(string theLine)
    {
        if (!socketReady)
            return;
        String foo = theLine + "\r\n";
        theWriter.Write(foo);
        theWriter.Flush();
    }
    public String readSocket()
    {   if (socketReady)
        {
            Byte[] data = new Byte[256];
            String responseData = String.Empty;
            NetworkStream stream = mySocket.GetStream();
            Int32 bytes = stream.Read(data, 0, data.Length);
            responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
            return responseData;
        }
        return "";
        
    }
    
    public void closeSocket()
    {
        if (!socketReady)
            return;
        theWriter.Close();
        theReader.Close();
        mySocket.Close();
        socketReady = false;
    }
    // end class s_TCP

    // Update is called once per frame
    private void Update()
    {
     
        if (Input.GetKeyDown("."))
        {
            writeSocket("z1");
            //string output = readSocket();
            //Debug.Log(output);
        }
        if (Input.GetKeyDown("/"))
        {
            writeSocket("x1");
        }
        if (Input.GetButtonDown("Fire3"))
        {
            closeSocket();
        }
        
        


    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (activated == false)
        {
            activated = true;
            writeSocket("Hello Kai");
            Debug.Log("it collides");
        }
        activated = false;
    }
    public void stopListening()
    {
        mRunning = false;
    }

    void OnApplicationQuit()
    { // stop listening thread
        stopListening();// wait for listening thread to terminate (max. 500ms)
        mThread.Join(500);
    }
}

