static int split_int8(const int8_t* in_data, int8_t** out_data, struct split_param* param)
{
    int slice_axis = param->axis;
    int num_slices = 1;
    int slice_size = 1; 
    for(int i = 0; i < slice_axis; i++)
    {
        num_slices = num_slices * param->input_shape.dim[i];
    }
    for(int i = slice_axis + 1; i < param->input_dim; i++)
    {
        slice_size = slice_size * param->input_shape.dim[i];
    }
    int in_slice =  param->input_shape.dim[slice_axis];
    int slice_index = 0;
    unsigned int out_num = param->output_counts;
    for(unsigned int i = 0; i < out_num; i++)
    {
        int8_t * output=(int8_t*)out_data[i];
        int out_slice = param->output_shape[i].dim[slice_axis];
        
        for(int n = 0; n < num_slices; n++)
        {
            int in_offset = (n * in_slice + slice_index) * slice_size;
            int out_offset  = n * out_slice * slice_size;
            memcpy(output+out_offset,in_data + in_offset,slice_size * out_slice * sizeof(int8_t));
        }
        slice_index += out_slice;       
    }

    return 0;
}
