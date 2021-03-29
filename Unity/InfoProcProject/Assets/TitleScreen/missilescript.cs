using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class missilescript : MonoBehaviour
{
    float speed = 1f;
    [SerializeField] GameObject explosion;
    [SerializeField] GameObject image;
    [SerializeField] GameObject backgroundfront;

    [SerializeField] GameObject startbutton;
    [SerializeField] GameObject ipput;
    [SerializeField] GameObject portput;
    [SerializeField] GameObject worldde10;
    [SerializeField] GameObject startmes;
    [SerializeField] GameObject ipmsg;
    [SerializeField] GameObject portmsg;
    [SerializeField] GameObject nuke;
    float timer = 1.6f;

    // Start is called before the first frame update
    void Start()
    {
        transform.position = new Vector3(0f, 7.8f, 0f);
    }

    // Update is called once per frame
    void Update()
    {
        if (transform.position.y > -3.7)
        {
            transform.position += Vector3.down * Time.deltaTime;
        }
        else
        {
            explosion.SetActive(true);
            image.SetActive(true);

            if (timer < 0)
            {
                backgroundfront.SetActive(false);
                startbutton.SetActive(true);
                ipput.SetActive(true);
                portput.SetActive(true);
                worldde10.SetActive(true);
                startmes.SetActive(true);
                ipmsg.SetActive(true);
                portmsg.SetActive(true);
                nuke.SetActive(true);
                Destroy(gameObject);
            }
            else
            {
                timer -= Time.deltaTime;
            }
        }
    }
}
