using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class reset : MonoBehaviour
{
    [SerializeField] SpriteRenderer sprite1;
    [SerializeField] SpriteRenderer sprite2;
    [SerializeField] Transform redtank;
    [SerializeField] Transform greentank;
    [SerializeField] Rigidbody2D redtank_rigid;
    [SerializeField] Rigidbody2D greentank_rigid;
    private Vector3 initial_pos_red;
    private Vector3 initial_pos_green;
    private Quaternion initial_rotation_red;
    private Quaternion initial_rotation_green;
    public bool redtankout = false;
    public bool greentankout = false;
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
    { if (collision.gameObject.CompareTag("chaser"))
        {
            redtankout = true;
            redtank.position = initial_pos_red;
            greentank.position = initial_pos_green;
            sprite1.color = Color.white;
            sprite2.color = Color.white;
            redtank_rigid.velocity = Vector3.zero;
            greentank_rigid.velocity = Vector3.zero;
        }
       else if (collision.gameObject.CompareTag("runner")){
            greentankout = true;
            redtank.position = initial_pos_red;
            greentank.position = initial_pos_green;
            sprite2.color = Color.white;
            sprite1.color = Color.white;
            redtank_rigid.velocity = Vector3.zero;
            greentank_rigid.velocity = Vector3.zero;
        }
    }
}
