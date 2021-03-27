using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class colochanger : MonoBehaviour
{
    private float a = 0;
    [SerializeField] movementde10 n;
    private bool firstrun = true;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if (a < 1.6 && (firstrun == true))
        {
            a += Time.deltaTime;
            GetComponent<RawImage>().color = new Color(255, 255, 255, a);
        }
        else 
        {
            firstrun = false;
            a -= Time.deltaTime;
            GetComponent<RawImage>().color = new Color(255, 255, 255, a);
        }
        if (a < 0.4 && firstrun == false)
        {
            n.canbeseen = true;
            Destroy(gameObject);
        }
    }
}
