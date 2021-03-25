using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class reset : MonoBehaviour
{
    [SerializeField] Transform redtank;
    [SerializeField] Transform greentank;
    [SerializeField] Rigidbody2D redtank_rigid;
    [SerializeField] Rigidbody2D greentank_rigid;
    private Vector3 initial_pos_red;
    private Vector3 initial_pos_green;
    // Start is called before the first frame update
    private void Awake()
    {
        initial_pos_green = greentank.transform.position;
        initial_pos_red = redtank.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    private void OnTriggerEnter2D(Collider2D collision)
    { if (collision.gameObject.CompareTag("chaser") || collision.gameObject.CompareTag("runner"))
        {
            redtank.position = initial_pos_red;
            greentank.position = initial_pos_green;
            redtank_rigid.velocity = Vector3.zero;
            greentank_rigid.velocity = Vector3.zero;
        }
    }
}
