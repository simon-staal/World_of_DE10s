using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class dontdespawn : MonoBehaviour
{
    // Start is called before the first frame update
    private void Awake()
    {
        DontDestroyOnLoad(this.gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
