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
    String Host = "";
    Int32 Port = 6969;
    public bool activated = false;
    // Start is called before the first frame update
    private bool mRunning;
    public Thread mThread;
    [SerializeField] runnerCharacterController instance;
    [SerializeField] characterController instance2;
    [SerializeField] reset resett;
    [SerializeField] time score;


    public GameObject scriptIp;
    Ipandportscript ipscript;


    public bool resetted = false;
    void Awake()
    {
        scriptIp = GameObject.Find("ipandport");
        if (scriptIp != null)
        {
            ipscript = scriptIp.GetComponent<Ipandportscript>();
            Host = ipscript.ip;
            Port = Int32.Parse(ipscript.po);
        }
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
        s = readSocket();
        writeSocket("r");
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
        if (resett.redtankout == true)
        {
            writeSocket("zn");

            resett.redtankout = false;
        }
        else if (resett.greentankout == true)
        {
            writeSocket("xn");
            resett.greentankout = false;
        }
        if (score.greenwins == true)
        {
            String s = readSocket();
            s = readSocket();
            writeSocket("xl");
            score.greenwins = false;
        }
        else if (score.redwins == true)
        {
            String s = readSocket();
            s = readSocket();
            writeSocket("zl");
            score.redwins = false;
        }
        if (Input.GetKeyDown("."))
        {
           // writeSocket("xl");
            //score.greenwins = false;
            //string output = readSocket();
            //Debug.Log(output);
        }
        if (Input.GetKeyDown("/"))
        {
            //writeSocket("zl");
        }
        if (Input.GetButtonDown("Fire3"))
        {
            //closeSocket();
        }
        
        


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

