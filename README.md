# Food Service Price Calculator (FSPC)
### Description
Takes input for case size variables, case cost, and desired portion sizes and outputs a suggested price per unit as well as an estimate for the amount of sales that can be made from each case of product.

### Example Usage
```
  [FSPC] Enter the number of units per case (i.e. bags): 6
    In this example think of the 6 as being the number of bags in a case of french fries...

  [FSPC] Enter the (per) unit size (in oz): 48
    The 48 represents the weight of french fries in ounces per bag in the case...
   
  [FSPC] Enter the cost per case: 64.99
    The 64.99 represents the amount paid by the business to the distributor per case of french fries...

  [FSPC] Enter the desired portion size (in oz): 8
    The portion size represents the amount that the business would like a cup of fries to contain...
    
  [FSPC] For a portion size of 8oz you should be charging ~$5.42 per sale with a total of ~36 available portions per case!
    This output displays that for optimal profit the business should sell each cup of fries for ~$5.42 and at ~100% efficiency will be able to make 36 cups of fries per case...
```

### Changing Variables
By default the multiplier for price is set to 3 / 300% as that is considered the optimal number for profit in the food industry. If you desire a different multiplier for some reason you can change the variable ``17:  const int cost_mult = 3;`` in ``fspc.cpp`` to whatever integer you would like.
