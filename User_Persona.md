## 2. User Persona

### Persona: Marcus Reed

**Name:** Marcus Reed  
**Age:** 34  
**Gender:** Male  
**Education:** Bachelor’s Degree in Mechanical Engineering  
**Location:** Rochester, NY  
**Living Situation:** Lives with his wife and young daughter in a single-family home  
**Occupation:** Electric bike repair technician and small business owner  
**Technical Experience:** Comfortable with basic electrical systems, battery packs, multimeters, and repair tools, but not an expert in embedded software or battery monitoring ICs  
**Hobbies:** Riding electric bikes, repairing electronics, camping, and teaching his daughter how things work  
**Favorite Brands:** Bosch, Anker, Milwaukee, Samsung  
**Devices Used:** Electric bike, portable power station, laptop, smartphone, and digital multimeter  

### Background

Marcus owns a small electric bike repair shop. Many of his customers bring in battery packs that are not charging correctly, losing range too quickly, or shutting off during use. Since battery problems can be dangerous, Marcus needs a reliable way to monitor battery voltage, current, and temperature before deciding whether a battery pack is safe to use.

Marcus is not designing battery management hardware from scratch, but he understands why battery safety matters. He wants a device that can clearly show whether a battery pack is healthy or unsafe. He does not want to guess based only on how the battery “feels” or how long it lasts during a ride.

### Goals

Marcus wants to use the Battery Management System to:

- Monitor individual battery cell voltages
- Detect unsafe voltage, current, and temperature conditions
- Prevent battery damage during charging and discharging
- Identify weak or unbalanced cells
- Improve customer safety
- Reduce the risk of overheating, short circuits, or battery failure

### Frustrations

Marcus gets frustrated when battery systems do not clearly explain what is wrong. Some battery packs simply stop working without showing whether the issue is low voltage, overcurrent, overheating, or cell imbalance. He also dislikes systems that require too much technical setup before they can provide useful information.

His biggest frustration is that battery failures can become dangerous quickly. If a battery pack overheats or a cell voltage becomes too high or too low, the user may not notice until the damage has already happened.

### Needs

Marcus needs the device to be:

- Safe and reliable
- Easy to connect to a battery pack
- Accurate enough to detect small voltage changes
- Able to warn the user when a fault occurs
- Capable of monitoring multiple cells in series
- Useful for both testing and real battery operation

### How Marcus Would Use the Device

Marcus would connect the Battery Management System to a rechargeable battery pack before testing or repairing it. The system would monitor each cell voltage, the total pack current, and the battery temperature. If the BMS detects an unsafe condition, such as overvoltage, undervoltage, overcurrent, or overheating, it would alert Marcus or trigger protection behavior.

For Marcus, the most important feature is trust. He needs to know that the system is constantly checking the battery and will respond if something becomes unsafe. This helps him protect his customers, his equipment, and his repair shop.

### Design Takeaway

This persona shows that the BMS should not only be technically functional, but also understandable to someone who works with batteries in real situations. The device should provide clear fault information, accurate measurements, and dependable protection so users like Marcus can make safe decisions without needing to understand every internal detail of the BQ76952 or microcontroller firmware.