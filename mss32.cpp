#include "stdafx.h"

#define MSS_DLL_EXPORT DLL_EXPORT

FARPROC pAIL_debug_printf;
FARPROC pAIL_sprintf;
FARPROC pDLSClose;
FARPROC pDLSCompactMemory;
FARPROC pDLSGetInfo;
FARPROC pDLSLoadFile;
FARPROC pDLSLoadMemFile;
FARPROC pDLSMSSOpen;
FARPROC pDLSSetAttribute;
FARPROC pDLSUnloadAll;
FARPROC pDLSUnloadFile;
FARPROC pRIB_alloc_provider_handle;
FARPROC pRIB_enumerate_interface;
FARPROC pRIB_error;
FARPROC pRIB_find_file_provider;
FARPROC pRIB_free_provider_handle;
FARPROC pRIB_free_provider_library;
FARPROC pRIB_load_provider_library;
FARPROC pRIB_register_interface;
FARPROC pRIB_request_interface;
FARPROC pRIB_request_interface_entry;
FARPROC pRIB_type_string;
FARPROC pRIB_unregister_interface;
FARPROC pAIL_3D_distance_factor;
FARPROC pAIL_3D_doppler_factor;
FARPROC pAIL_3D_orientation;
FARPROC pAIL_3D_position;
FARPROC pAIL_3D_provider_attribute;
FARPROC pAIL_3D_rolloff_factor;
FARPROC pAIL_3D_room_type;
FARPROC pAIL_3D_sample_attribute;
FARPROC pAIL_3D_sample_cone;
FARPROC pAIL_3D_sample_distances;
FARPROC pAIL_3D_sample_effects_level;
FARPROC pAIL_3D_sample_exclusion;
FARPROC pAIL_3D_sample_length;
FARPROC pAIL_3D_sample_loop_count;
FARPROC pAIL_3D_sample_obstruction;
FARPROC pAIL_3D_sample_occlusion;
FARPROC pAIL_3D_sample_offset;
FARPROC pAIL_3D_sample_playback_rate;
FARPROC pAIL_3D_sample_status;
FARPROC pAIL_3D_sample_volume;
FARPROC pAIL_3D_speaker_type;
FARPROC pAIL_3D_user_data;
FARPROC pAIL_3D_velocity;
FARPROC pAIL_DLS_close;
FARPROC pAIL_DLS_compact;
FARPROC pAIL_DLS_get_info;
FARPROC pAIL_DLS_get_reverb_levels;
FARPROC pAIL_DLS_load_file;
FARPROC pAIL_DLS_load_memory;
FARPROC pAIL_DLS_open;
FARPROC pAIL_DLS_set_reverb_levels;
FARPROC pAIL_DLS_unload;
FARPROC pAIL_HWND;
FARPROC pAIL_MIDI_handle_reacquire;
FARPROC pAIL_MIDI_handle_release;
FARPROC pAIL_MIDI_to_XMI;
FARPROC pAIL_MMX_available;
FARPROC pAIL_WAV_file_write;
FARPROC pAIL_WAV_info;
FARPROC pAIL_XMIDI_master_volume;
FARPROC pAIL_active_3D_sample_count;
FARPROC pAIL_active_sample_count;
FARPROC pAIL_active_sequence_count;
FARPROC pAIL_allocate_3D_sample_handle;
FARPROC pAIL_allocate_file_sample;
FARPROC pAIL_allocate_sample_handle;
FARPROC pAIL_allocate_sequence_handle;
FARPROC pAIL_auto_service_stream;
FARPROC pAIL_auto_update_3D_position;
FARPROC pAIL_background;
FARPROC pAIL_branch_index;
FARPROC pAIL_channel_notes;
FARPROC pAIL_close_3D_listener;
FARPROC pAIL_close_3D_object;
FARPROC pAIL_close_3D_provider;
FARPROC pAIL_close_XMIDI_driver;
FARPROC pAIL_close_digital_driver;
FARPROC pAIL_close_filter;
FARPROC pAIL_close_input;
FARPROC pAIL_close_stream;
FARPROC pAIL_compress_ADPCM;
FARPROC pAIL_compress_ASI;
FARPROC pAIL_compress_DLS;
FARPROC pAIL_controller_value;
FARPROC pAIL_create_wave_synthesizer;
FARPROC pAIL_decompress_ADPCM;
FARPROC pAIL_decompress_ASI;
FARPROC pAIL_delay;
FARPROC pAIL_destroy_wave_synthesizer;
FARPROC pAIL_digital_CPU_percent;
FARPROC pAIL_digital_configuration;
FARPROC pAIL_digital_handle_reacquire;
FARPROC pAIL_digital_handle_release;
FARPROC pAIL_digital_latency;
FARPROC pAIL_digital_master_reverb;
FARPROC pAIL_digital_master_reverb_levels;
FARPROC pAIL_digital_master_volume_level;
FARPROC pAIL_end_3D_sample;
FARPROC pAIL_end_sample;
FARPROC pAIL_end_sequence;
FARPROC pAIL_enumerate_3D_provider_attributes;
FARPROC pAIL_enumerate_3D_providers;
FARPROC pAIL_enumerate_3D_sample_attributes;
FARPROC pAIL_enumerate_filter_attributes;
FARPROC pAIL_enumerate_filter_sample_attributes;
FARPROC pAIL_enumerate_filters;
FARPROC pAIL_extract_DLS;
FARPROC pAIL_file_error;
FARPROC pAIL_file_read;
FARPROC pAIL_file_size;
FARPROC pAIL_file_type;
FARPROC pAIL_file_write;
FARPROC pAIL_filter_DLS_attribute;
FARPROC pAIL_filter_DLS_with_XMI;
FARPROC pAIL_filter_attribute;
FARPROC pAIL_filter_sample_attribute;
FARPROC pAIL_filter_stream_attribute;
FARPROC pAIL_find_DLS;
FARPROC pAIL_get_DirectSound_info;
FARPROC pAIL_get_input_info;
FARPROC pAIL_get_preference;
FARPROC pAIL_get_timer_highest_delay;
FARPROC pAIL_init_sample;
FARPROC pAIL_init_sequence;
FARPROC pAIL_last_error;
FARPROC pAIL_list_DLS;
FARPROC pAIL_list_MIDI;
FARPROC pAIL_load_sample_buffer;
FARPROC pAIL_lock;
FARPROC pAIL_lock_channel;
FARPROC pAIL_lock_mutex;
FARPROC pAIL_map_sequence_channel;
FARPROC pAIL_mem_alloc_lock;
FARPROC pAIL_mem_free_lock;
FARPROC pAIL_mem_use_free;
FARPROC pAIL_mem_use_malloc;
FARPROC pAIL_merge_DLS_with_XMI;
FARPROC pAIL_midiOutClose;
FARPROC pAIL_midiOutOpen;
FARPROC pAIL_minimum_sample_buffer_size;
FARPROC pAIL_ms_count;
FARPROC pAIL_open_3D_listener;
FARPROC pAIL_open_3D_object;
FARPROC pAIL_open_3D_provider;
FARPROC pAIL_open_XMIDI_driver;
FARPROC pAIL_open_digital_driver;
FARPROC pAIL_open_filter;
FARPROC pAIL_open_input;
FARPROC pAIL_open_stream;
FARPROC pAIL_pause_stream;
FARPROC pAIL_primary_digital_driver;
FARPROC pAIL_process_digital_audio;
FARPROC pAIL_quick_copy;
FARPROC pAIL_quick_halt;
FARPROC pAIL_quick_handles;
FARPROC pAIL_quick_load;
FARPROC pAIL_quick_load_and_play;
FARPROC pAIL_quick_load_mem;
FARPROC pAIL_quick_ms_length;
FARPROC pAIL_quick_ms_position;
FARPROC pAIL_quick_play;
FARPROC pAIL_quick_set_low_pass_cut_off;
FARPROC pAIL_quick_set_ms_position;
FARPROC pAIL_quick_set_reverb_levels;
FARPROC pAIL_quick_set_speed;
FARPROC pAIL_quick_set_volume;
FARPROC pAIL_quick_shutdown;
FARPROC pAIL_quick_startup;
FARPROC pAIL_quick_status;
FARPROC pAIL_quick_type;
FARPROC pAIL_quick_unload;
FARPROC pAIL_redbook_close;
FARPROC pAIL_redbook_eject;
FARPROC pAIL_redbook_id;
FARPROC pAIL_redbook_open;
FARPROC pAIL_redbook_open_drive;
FARPROC pAIL_redbook_pause;
FARPROC pAIL_redbook_play;
FARPROC pAIL_redbook_position;
FARPROC pAIL_redbook_resume;
FARPROC pAIL_redbook_retract;
FARPROC pAIL_redbook_set_volume_level;
FARPROC pAIL_redbook_status;
FARPROC pAIL_redbook_stop;
FARPROC pAIL_redbook_track;
FARPROC pAIL_redbook_track_info;
FARPROC pAIL_redbook_tracks;
FARPROC pAIL_redbook_volume_level;
FARPROC pAIL_register_3D_EOS_callback;
FARPROC pAIL_register_EOB_callback;
FARPROC pAIL_register_EOF_callback;
FARPROC pAIL_register_EOS_callback;
FARPROC pAIL_register_ICA_array;
FARPROC pAIL_register_SOB_callback;
FARPROC pAIL_register_beat_callback;
FARPROC pAIL_register_event_callback;
FARPROC pAIL_register_prefix_callback;
FARPROC pAIL_register_sequence_callback;
FARPROC pAIL_register_stream_callback;
FARPROC pAIL_register_timbre_callback;
FARPROC pAIL_register_timer;
FARPROC pAIL_register_trigger_callback;
FARPROC pAIL_release_3D_sample_handle;
FARPROC pAIL_release_all_timers;
FARPROC pAIL_release_channel;
FARPROC pAIL_release_sample_handle;
FARPROC pAIL_release_sequence_handle;
FARPROC pAIL_release_timer_handle;
FARPROC pAIL_request_EOB_ASI_reset;
FARPROC pAIL_resume_3D_sample;
FARPROC pAIL_resume_sample;
FARPROC pAIL_resume_sequence;
FARPROC pAIL_sample_buffer_info;
FARPROC pAIL_sample_buffer_ready;
FARPROC pAIL_sample_granularity;
FARPROC pAIL_sample_loop_count;
FARPROC pAIL_sample_low_pass_cut_off;
FARPROC pAIL_sample_ms_position;
FARPROC pAIL_sample_playback_rate;
FARPROC pAIL_sample_position;
FARPROC pAIL_sample_reverb_levels;
FARPROC pAIL_sample_status;
FARPROC pAIL_sample_user_data;
FARPROC pAIL_sample_volume_levels;
FARPROC pAIL_sample_volume_pan;
FARPROC pAIL_send_channel_voice_message;
FARPROC pAIL_send_sysex_message;
FARPROC pAIL_sequence_loop_count;
FARPROC pAIL_sequence_ms_position;
FARPROC pAIL_sequence_position;
FARPROC pAIL_sequence_status;
FARPROC pAIL_sequence_tempo;
FARPROC pAIL_sequence_user_data;
FARPROC pAIL_sequence_volume;
FARPROC pAIL_serve;
FARPROC pAIL_service_stream;
FARPROC pAIL_set_3D_distance_factor;
FARPROC pAIL_set_3D_doppler_factor;
FARPROC pAIL_set_3D_orientation;
FARPROC pAIL_set_3D_position;
FARPROC pAIL_set_3D_provider_preference;
FARPROC pAIL_set_3D_rolloff_factor;
FARPROC pAIL_set_3D_room_type;
FARPROC pAIL_set_3D_sample_cone;
FARPROC pAIL_set_3D_sample_distances;
FARPROC pAIL_set_3D_sample_effects_level;
FARPROC pAIL_set_3D_sample_exclusion;
FARPROC pAIL_set_3D_sample_file;
FARPROC pAIL_set_3D_sample_info;
FARPROC pAIL_set_3D_sample_loop_block;
FARPROC pAIL_set_3D_sample_loop_count;
FARPROC pAIL_set_3D_sample_obstruction;
FARPROC pAIL_set_3D_sample_occlusion;
FARPROC pAIL_set_3D_sample_offset;
FARPROC pAIL_set_3D_sample_playback_rate;
FARPROC pAIL_set_3D_sample_preference;
FARPROC pAIL_set_3D_sample_volume;
FARPROC pAIL_set_3D_speaker_type;
FARPROC pAIL_set_3D_user_data;
FARPROC pAIL_set_3D_velocity;
FARPROC pAIL_set_3D_velocity_vector;
FARPROC pAIL_set_DLS_processor;
FARPROC pAIL_set_DirectSound_HWND;
FARPROC pAIL_set_XMIDI_master_volume;
FARPROC pAIL_set_digital_driver_processor;
FARPROC pAIL_set_digital_master_reverb;
FARPROC pAIL_set_digital_master_reverb_levels;
FARPROC pAIL_set_digital_master_room_type;
FARPROC pAIL_set_digital_master_volume_level;
FARPROC pAIL_set_error;
FARPROC pAIL_set_file_async_callbacks;
FARPROC pAIL_set_file_callbacks;
FARPROC pAIL_set_filter_DLS_preference;
FARPROC pAIL_set_filter_preference;
FARPROC pAIL_set_filter_sample_preference;
FARPROC pAIL_set_filter_stream_preference;
FARPROC pAIL_set_input_state;
FARPROC pAIL_set_named_sample_file;
FARPROC pAIL_set_preference;
FARPROC pAIL_set_redist_directory;
FARPROC pAIL_set_sample_address;
FARPROC pAIL_set_sample_adpcm_block_size;
FARPROC pAIL_set_sample_file;
FARPROC pAIL_set_sample_loop_block;
FARPROC pAIL_set_sample_loop_count;
FARPROC pAIL_set_sample_low_pass_cut_off;
FARPROC pAIL_set_sample_ms_position;
FARPROC pAIL_set_sample_playback_rate;
FARPROC pAIL_set_sample_position;
FARPROC pAIL_set_sample_processor;
FARPROC pAIL_set_sample_reverb_levels;
FARPROC pAIL_set_sample_type;
FARPROC pAIL_set_sample_user_data;
FARPROC pAIL_set_sample_volume_levels;
FARPROC pAIL_set_sample_volume_pan;
FARPROC pAIL_set_sequence_loop_count;
FARPROC pAIL_set_sequence_ms_position;
FARPROC pAIL_set_sequence_tempo;
FARPROC pAIL_set_sequence_user_data;
FARPROC pAIL_set_sequence_volume;
FARPROC pAIL_set_stream_loop_block;
FARPROC pAIL_set_stream_loop_count;
FARPROC pAIL_set_stream_low_pass_cut_off;
FARPROC pAIL_set_stream_ms_position;
FARPROC pAIL_set_stream_playback_rate;
FARPROC pAIL_set_stream_position;
FARPROC pAIL_set_stream_processor;
FARPROC pAIL_set_stream_reverb_levels;
FARPROC pAIL_set_stream_user_data;
FARPROC pAIL_set_stream_volume_levels;
FARPROC pAIL_set_stream_volume_pan;
FARPROC pAIL_set_timer_divisor;
FARPROC pAIL_set_timer_frequency;
FARPROC pAIL_set_timer_period;
FARPROC pAIL_set_timer_user;
FARPROC pAIL_shutdown;
FARPROC pAIL_size_processed_digital_audio;
FARPROC pAIL_start_3D_sample;
FARPROC pAIL_start_all_timers;
FARPROC pAIL_start_sample;
FARPROC pAIL_start_sequence;
FARPROC pAIL_start_stream;
FARPROC pAIL_start_timer;
FARPROC pAIL_startup;
FARPROC pAIL_stop_3D_sample;
FARPROC pAIL_stop_all_timers;
FARPROC pAIL_stop_sample;
FARPROC pAIL_stop_sequence;
FARPROC pAIL_stop_timer;
FARPROC pAIL_stream_info;
FARPROC pAIL_stream_loop_count;
FARPROC pAIL_stream_low_pass_cut_off;
FARPROC pAIL_stream_ms_position;
FARPROC pAIL_stream_playback_rate;
FARPROC pAIL_stream_position;
FARPROC pAIL_stream_reverb_levels;
FARPROC pAIL_stream_status;
FARPROC pAIL_stream_user_data;
FARPROC pAIL_stream_volume_levels;
FARPROC pAIL_stream_volume_pan;
FARPROC pAIL_true_sequence_channel;
FARPROC pAIL_unlock;
FARPROC pAIL_unlock_mutex;
FARPROC pAIL_update_3D_position;
FARPROC pAIL_us_count;
FARPROC pAIL_waveOutClose;
FARPROC pAIL_waveOutOpen;
FARPROC pDLSMSSGetCPU;
FARPROC pMIX_RIB_MAIN;
FARPROC pRIB_enumerate_providers;
FARPROC pRIB_find_file_dec_provider;
FARPROC pRIB_find_files_provider;
FARPROC pRIB_find_provider;
FARPROC pRIB_load_application_providers;
FARPROC pRIB_load_static_provider_library;
FARPROC pRIB_provider_system_data;
FARPROC pRIB_provider_user_data;
FARPROC pRIB_set_provider_system_data;
FARPROC pRIB_set_provider_user_data;
FARPROC pstream_background;

extern "C" {

	static HMODULE hMSS = NULL;

	typedef void(*Com_Printf_t)(const char*, ...);
	Com_Printf_t Com_Printf_o = (Com_Printf_t)0x4357B0;

	char printmsg[1024] = { 0 };
	void Com_Printf(const char *s) {

		extern int codversion;

		if (codversion != COD_1)
			return;

		if (!strcmp(printmsg, s))
			return;

		strncpy(printmsg, s, sizeof(printmsg) - 1);

		//Com_Printf_o(s);
	}

	__declspec(naked) MSS_DLL_EXPORT void AIL_debug_printf() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pAIL_debug_printf]
	}
	__declspec(naked) MSS_DLL_EXPORT void AIL_sprintf() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pAIL_sprintf]
	}
	__declspec(naked) MSS_DLL_EXPORT void DLSClose() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pDLSClose]
	}
	__declspec(naked) MSS_DLL_EXPORT void DLSCompactMemory() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pDLSCompactMemory]
	}
	__declspec(naked) MSS_DLL_EXPORT void DLSGetInfo() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pDLSGetInfo]
	}
	__declspec(naked) MSS_DLL_EXPORT void DLSLoadFile() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pDLSLoadFile]
	}
	__declspec(naked) MSS_DLL_EXPORT void DLSLoadMemFile() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pDLSLoadMemFile]
	}
	__declspec(naked) MSS_DLL_EXPORT void DLSMSSOpen() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pDLSMSSOpen]
	}
	__declspec(naked) MSS_DLL_EXPORT void DLSSetAttribute() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pDLSSetAttribute]
	}
	__declspec(naked) MSS_DLL_EXPORT void DLSUnloadAll() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pDLSUnloadAll]
	}
	__declspec(naked) MSS_DLL_EXPORT void DLSUnloadFile() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pDLSUnloadFile]
	}
	__declspec(naked) MSS_DLL_EXPORT void RIB_alloc_provider_handle() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_alloc_provider_handle]
	}
	__declspec(naked) MSS_DLL_EXPORT void RIB_enumerate_interface() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_enumerate_interface]
	}
	__declspec(naked) MSS_DLL_EXPORT void RIB_error() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_error]
	}
	__declspec(naked) MSS_DLL_EXPORT void RIB_find_file_provider() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_find_file_provider]
	}
	__declspec(naked) MSS_DLL_EXPORT void RIB_free_provider_handle() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_free_provider_handle]
	}
	__declspec(naked) MSS_DLL_EXPORT void RIB_free_provider_library() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_free_provider_library]
	}
	__declspec(naked) MSS_DLL_EXPORT void RIB_load_provider_library() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_load_provider_library]
	}
	__declspec(naked) MSS_DLL_EXPORT void RIB_register_interface() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_register_interface]
	}
	__declspec(naked) MSS_DLL_EXPORT void RIB_request_interface() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_request_interface]
	}
	__declspec(naked) MSS_DLL_EXPORT void RIB_request_interface_entry() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_request_interface_entry]
	}
	__declspec(naked) MSS_DLL_EXPORT void RIB_type_string() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_type_string]
	}
	__declspec(naked) MSS_DLL_EXPORT void RIB_unregister_interface() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_unregister_interface]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_distance_factor(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_distance_factor\n");
		__asm jmp[pAIL_3D_distance_factor]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_doppler_factor(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_doppler_factor\n");
		__asm jmp[pAIL_3D_doppler_factor]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_orientation(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q, DWORD u, DWORD y) {
		Com_Printf("^2Miles Debug: AIL_3D_orientation\n");
		__asm jmp[pAIL_3D_orientation]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_position(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_3D_position\n");
		__asm jmp[pAIL_3D_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_provider_attribute(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_3D_provider_attribute\n");
		__asm jmp[pAIL_3D_provider_attribute]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_rolloff_factor(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_rolloff_factor\n");
		__asm jmp[pAIL_3D_rolloff_factor]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_room_type(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_room_type\n");
		__asm jmp[pAIL_3D_room_type]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_attribute(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_3D_sample_attribute\n");
		__asm jmp[pAIL_3D_sample_attribute]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_cone(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_3D_sample_cone\n");
		__asm jmp[pAIL_3D_sample_cone]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_distances(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_3D_sample_distances\n");
		__asm jmp[pAIL_3D_sample_distances]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_effects_level(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_sample_effects_level\n");
		__asm jmp[pAIL_3D_sample_effects_level]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_exclusion(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_sample_exclusion\n");
		__asm jmp[pAIL_3D_sample_exclusion]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_length(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_sample_length\n");
		__asm jmp[pAIL_3D_sample_length]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_loop_count(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_sample_loop_count\n");
		__asm jmp[pAIL_3D_sample_loop_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_obstruction(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_sample_obstruction\n");
		__asm jmp[pAIL_3D_sample_obstruction]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_occlusion(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_sample_occlusion\n");
		__asm jmp[pAIL_3D_sample_occlusion]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_offset(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_sample_offset\n");
		__asm jmp[pAIL_3D_sample_offset]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_playback_rate(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_sample_playback_rate\n");
		__asm jmp[pAIL_3D_sample_playback_rate]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_status(DWORD a) {
		//Com_Printf("^2Miles Debug: AIL_3D_sample_status\n"); //stop being sonic
		__asm jmp[pAIL_3D_sample_status]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_sample_volume(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_sample_volume\n");
		__asm jmp[pAIL_3D_sample_volume]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_speaker_type(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_3D_speaker_type\n");
		__asm jmp[pAIL_3D_speaker_type]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_user_data(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_3D_user_data\n");
		__asm jmp[pAIL_3D_user_data]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_3D_velocity(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_3D_velocity\n");
		__asm jmp[pAIL_3D_velocity]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_DLS_close(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_DLS_close\n");
		__asm jmp[pAIL_DLS_close]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_DLS_compact(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_DLS_compact\n");
		__asm jmp[pAIL_DLS_compact]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_DLS_get_info(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_DLS_get_info\n");
		__asm jmp[pAIL_DLS_get_info]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_DLS_get_reverb_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_DLS_get_reverb_levels\n");
		__asm jmp[pAIL_DLS_get_reverb_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_DLS_load_file(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_DLS_load_file\n");
		__asm jmp[pAIL_DLS_load_file]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_DLS_load_memory(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_DLS_load_memory\n");
		__asm jmp[pAIL_DLS_load_memory]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_DLS_open(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q, DWORD u, DWORD y) {
		Com_Printf("^2Miles Debug: AIL_DLS_open\n");
		__asm jmp[pAIL_DLS_open]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_DLS_set_reverb_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_DLS_set_reverb_levels\n");
		__asm jmp[pAIL_DLS_set_reverb_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_DLS_unload(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_DLS_unload\n");
		__asm jmp[pAIL_DLS_unload]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_HWND() {
		Com_Printf("^2Miles Debug: AIL_HWND\n");
		__asm jmp[pAIL_HWND]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_MIDI_handle_reacquire(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_MIDI_handle_reacquire\n");
		__asm jmp[pAIL_MIDI_handle_reacquire]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_MIDI_handle_release(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_MIDI_handle_release\n");
		__asm jmp[pAIL_MIDI_handle_release]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_MIDI_to_XMI(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_MIDI_to_XMI\n");
		__asm jmp[pAIL_MIDI_to_XMI]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_MMX_available() {
		Com_Printf("^2Miles Debug: AIL_MMX_available\n");
		__asm jmp[pAIL_MMX_available]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_WAV_file_write(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_WAV_file_write\n");
		__asm jmp[pAIL_WAV_file_write]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_WAV_info(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_WAV_info\n");
		__asm jmp[pAIL_WAV_info]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_XMIDI_master_volume(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_XMIDI_master_volume\n");
		__asm jmp[pAIL_XMIDI_master_volume]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_active_3D_sample_count(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_active_3D_sample_count\n");
		__asm jmp[pAIL_active_3D_sample_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_active_sample_count(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_active_sample_count\n");
		__asm jmp[pAIL_active_sample_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_active_sequence_count(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_active_sequence_count\n");
		__asm jmp[pAIL_active_sequence_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_allocate_3D_sample_handle(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_allocate_3D_sample_handle\n");
		__asm jmp[pAIL_allocate_3D_sample_handle]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_allocate_file_sample(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_allocate_file_sample\n");
		__asm jmp[pAIL_allocate_file_sample]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_allocate_sample_handle(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_allocate_sample_handle\n");
		__asm jmp[pAIL_allocate_sample_handle]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_allocate_sequence_handle(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_allocate_sequence_handle\n");
		__asm jmp[pAIL_allocate_sequence_handle]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_auto_service_stream(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_auto_service_stream\n");
		__asm jmp[pAIL_auto_service_stream]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_auto_update_3D_position(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_auto_update_3D_position\n");
		__asm jmp[pAIL_auto_update_3D_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_background() {
		Com_Printf("^2Miles Debug: AIL_background\n");
		__asm jmp[pAIL_background]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_branch_index(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_branch_index\n");
		__asm jmp[pAIL_branch_index]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_channel_notes(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_channel_notes\n");
		__asm jmp[pAIL_channel_notes]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_close_3D_listener(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_close_3D_listener\n");
		__asm jmp[pAIL_close_3D_listener]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_close_3D_object(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_close_3D_object\n");
		__asm jmp[pAIL_close_3D_object]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_close_3D_provider(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_close_3D_provider\n");
		__asm jmp[pAIL_close_3D_provider]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_close_XMIDI_driver(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_close_XMIDI_driver\n");
		__asm jmp[pAIL_close_XMIDI_driver]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_close_digital_driver(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_close_digital_driver\n");
		__asm jmp[pAIL_close_digital_driver]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_close_filter(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_close_filter\n");
		__asm jmp[pAIL_close_filter]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_close_input(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_close_input\n");
		__asm jmp[pAIL_close_input]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_close_stream(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_close_stream\n");
		__asm jmp[pAIL_close_stream]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_compress_ADPCM(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_compress_ADPCM\n");
		__asm jmp[pAIL_compress_ADPCM]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_compress_ASI(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_compress_ASI\n");
		__asm jmp[pAIL_compress_ASI]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_compress_DLS(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_compress_DLS\n");
		__asm jmp[pAIL_compress_DLS]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_controller_value(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_controller_value\n");
		__asm jmp[pAIL_controller_value]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_create_wave_synthesizer(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_create_wave_synthesizer\n");
		__asm jmp[pAIL_create_wave_synthesizer]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_decompress_ADPCM(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_decompress_ADPCM\n");
		__asm jmp[pAIL_decompress_ADPCM]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_decompress_ASI(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q, DWORD u) {
		Com_Printf("^2Miles Debug: AIL_decompress_ASI\n");
		__asm jmp[pAIL_decompress_ASI]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_delay(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_delay\n");
		__asm jmp[pAIL_delay]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_destroy_wave_synthesizer(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_destroy_wave_synthesizer\n");
		__asm jmp[pAIL_destroy_wave_synthesizer]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_digital_CPU_percent(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_digital_CPU_percent\n");
		__asm jmp[pAIL_digital_CPU_percent]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_digital_configuration(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_digital_configuration\n");
		__asm jmp[pAIL_digital_configuration]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_digital_handle_reacquire(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_digital_handle_reacquire\n");
		__asm jmp[pAIL_digital_handle_reacquire]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_digital_handle_release(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_digital_handle_release\n");
		__asm jmp[pAIL_digital_handle_release]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_digital_latency(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_digital_latency\n");
		__asm jmp[pAIL_digital_latency]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_digital_master_reverb(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_digital_master_reverb\n");
		__asm jmp[pAIL_digital_master_reverb]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_digital_master_reverb_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_digital_master_reverb_levels\n");
		__asm jmp[pAIL_digital_master_reverb_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_digital_master_volume_level(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_digital_master_volume_level\n");
		__asm jmp[pAIL_digital_master_volume_level]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_end_3D_sample(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_end_3D_sample\n");
		__asm jmp[pAIL_end_3D_sample]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_end_sample(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_end_sample\n");
		__asm jmp[pAIL_end_sample]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_end_sequence(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_end_sequence\n");
		__asm jmp[pAIL_end_sequence]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_enumerate_3D_provider_attributes(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_enumerate_3D_provider_attributes\n");
		__asm jmp[pAIL_enumerate_3D_provider_attributes]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_enumerate_3D_providers(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_enumerate_3D_providers\n");
		__asm jmp[pAIL_enumerate_3D_providers]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_enumerate_3D_sample_attributes(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_enumerate_3D_sample_attributes\n");
		__asm jmp[pAIL_enumerate_3D_sample_attributes]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_enumerate_filter_attributes(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_enumerate_filter_attributes\n");
		__asm jmp[pAIL_enumerate_filter_attributes]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_enumerate_filter_sample_attributes(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_enumerate_filter_sample_attributes\n");
		__asm jmp[pAIL_enumerate_filter_sample_attributes]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_enumerate_filters(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_enumerate_filters\n");
		__asm jmp[pAIL_enumerate_filters]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_extract_DLS(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q, DWORD u, DWORD y) {
		Com_Printf("^2Miles Debug: AIL_extract_DLS\n");
		__asm jmp[pAIL_extract_DLS]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_file_error() {
		Com_Printf("^2Miles Debug: AIL_file_error\n");
		__asm jmp[pAIL_file_error]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_file_read(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_file_read\n");
		__asm jmp[pAIL_file_read]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_file_size(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_file_size\n");
		__asm jmp[pAIL_file_size]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_file_type(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_file_type\n");
		__asm jmp[pAIL_file_type]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_file_write(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_file_write\n");
		__asm jmp[pAIL_file_write]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_filter_DLS_attribute(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_filter_DLS_attribute\n");
		__asm jmp[pAIL_filter_DLS_attribute]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_filter_DLS_with_XMI(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q, DWORD u) {
		Com_Printf("^2Miles Debug: AIL_filter_DLS_with_XMI\n");
		__asm jmp[pAIL_filter_DLS_with_XMI]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_filter_attribute(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_filter_attribute\n");
		__asm jmp[pAIL_filter_attribute]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_filter_sample_attribute(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_filter_sample_attribute\n");
		__asm jmp[pAIL_filter_sample_attribute]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_filter_stream_attribute(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_filter_stream_attribute\n");
		__asm jmp[pAIL_filter_stream_attribute]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_find_DLS(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q, DWORD u) {
		Com_Printf("^2Miles Debug: AIL_find_DLS\n");
		__asm jmp[pAIL_find_DLS]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_get_DirectSound_info(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_get_DirectSound_info\n");
		__asm jmp[pAIL_get_DirectSound_info]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_get_input_info(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_get_input_info\n");
		__asm jmp[pAIL_get_input_info]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_get_preference(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_get_preference\n");
		__asm jmp[pAIL_get_preference]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_get_timer_highest_delay() {
		Com_Printf("^2Miles Debug: AIL_get_timer_highest_delay\n");
		__asm jmp[pAIL_get_timer_highest_delay]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_init_sample(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_init_sample\n");
		__asm jmp[pAIL_init_sample]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_init_sequence(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_init_sequence\n");
		__asm jmp[pAIL_init_sequence]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_last_error() {
		Com_Printf("^2Miles Debug: AIL_last_error\n");
		__asm jmp[pAIL_last_error]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_list_DLS(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_list_DLS\n");
		__asm jmp[pAIL_list_DLS]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_list_MIDI(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_list_MIDI\n");
		__asm jmp[pAIL_list_MIDI]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_load_sample_buffer(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_load_sample_buffer\n");
		__asm jmp[pAIL_load_sample_buffer]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_lock() {
		Com_Printf("^2Miles Debug: AIL_lock\n");
		__asm jmp[pAIL_lock]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_lock_channel(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_lock_channel\n");
		__asm jmp[pAIL_lock_channel]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_lock_mutex() {
		Com_Printf("^2Miles Debug: AIL_lock_mutex\n");
		__asm jmp[pAIL_lock_mutex]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_map_sequence_channel(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_map_sequence_channel\n");
		__asm jmp[pAIL_map_sequence_channel]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_mem_alloc_lock(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_mem_alloc_lock\n");
		__asm jmp[pAIL_mem_alloc_lock]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_mem_free_lock(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_mem_free_lock\n");
		__asm jmp[pAIL_mem_free_lock]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_mem_use_free(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_mem_use_free\n");
		__asm jmp[pAIL_mem_use_free]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_mem_use_malloc(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_mem_use_malloc\n");
		__asm jmp[pAIL_mem_use_malloc]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_merge_DLS_with_XMI(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_merge_DLS_with_XMI\n");
		__asm jmp[pAIL_merge_DLS_with_XMI]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_midiOutClose(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_midiOutClose\n");
		__asm jmp[pAIL_midiOutClose]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_midiOutOpen(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_midiOutOpen\n");
		__asm jmp[pAIL_midiOutOpen]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_minimum_sample_buffer_size(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_minimum_sample_buffer_size\n");
		__asm jmp[pAIL_minimum_sample_buffer_size]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_ms_count() {
		Com_Printf("^2Miles Debug: AIL_ms_count\n");
		__asm jmp[pAIL_ms_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_open_3D_listener(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_open_3D_listener\n");
		__asm jmp[pAIL_open_3D_listener]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_open_3D_object(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_open_3D_object\n");
		__asm jmp[pAIL_open_3D_object]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_open_3D_provider(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_open_3D_provider\n");
		__asm jmp[pAIL_open_3D_provider]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_open_XMIDI_driver(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_open_XMIDI_driver\n");
		__asm jmp[pAIL_open_XMIDI_driver]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_open_digital_driver(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_open_digital_driver\n");
		__asm jmp[pAIL_open_digital_driver]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_open_filter(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_open_filter\n");
		__asm jmp[pAIL_open_filter]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_open_input(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_open_input\n");
		__asm jmp[pAIL_open_input]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_open_stream(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_open_stream\n");
		__asm jmp[pAIL_open_stream]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_pause_stream(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_pause_stream\n");
		__asm jmp[pAIL_pause_stream]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_primary_digital_driver(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_primary_digital_driver\n");
		__asm jmp[pAIL_primary_digital_driver]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_process_digital_audio(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q, DWORD u) {
		Com_Printf("^2Miles Debug: AIL_process_digital_audio\n");
		__asm jmp[pAIL_process_digital_audio]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_copy(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_quick_copy\n");
		__asm jmp[pAIL_quick_copy]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_halt(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_quick_halt\n");
		__asm jmp[pAIL_quick_halt]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_handles(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_quick_handles\n");
		__asm jmp[pAIL_quick_handles]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_load(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_quick_load\n");
		__asm jmp[pAIL_quick_load]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_load_and_play(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_quick_load_and_play\n");
		__asm jmp[pAIL_quick_load_and_play]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_load_mem(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_quick_load_mem\n");
		__asm jmp[pAIL_quick_load_mem]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_ms_length(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_quick_ms_length\n");
		__asm jmp[pAIL_quick_ms_length]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_ms_position(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_quick_ms_position\n");
		__asm jmp[pAIL_quick_ms_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_play(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_quick_play\n");
		__asm jmp[pAIL_quick_play]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_set_low_pass_cut_off(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_quick_set_low_pass_cut_off\n");
		__asm jmp[pAIL_quick_set_low_pass_cut_off]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_set_ms_position(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_quick_set_ms_position\n");
		__asm jmp[pAIL_quick_set_ms_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_set_reverb_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_quick_set_reverb_levels\n");
		__asm jmp[pAIL_quick_set_reverb_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_set_speed(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_quick_set_speed\n");
		__asm jmp[pAIL_quick_set_speed]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_set_volume(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_quick_set_volume\n");
		__asm jmp[pAIL_quick_set_volume]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_shutdown() {
		Com_Printf("^2Miles Debug: AIL_quick_shutdown\n");
		__asm jmp[pAIL_quick_shutdown]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_startup(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_quick_startup\n");
		__asm jmp[pAIL_quick_startup]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_status(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_quick_status\n");
		__asm jmp[pAIL_quick_status]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_type(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_quick_type\n");
		__asm jmp[pAIL_quick_type]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_quick_unload(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_quick_unload\n");
		__asm jmp[pAIL_quick_unload]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_close(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_close\n");
		__asm jmp[pAIL_redbook_close]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_eject(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_eject\n");
		__asm jmp[pAIL_redbook_eject]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_id(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_id\n");
		__asm jmp[pAIL_redbook_id]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_open(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_open\n");
		__asm jmp[pAIL_redbook_open]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_open_drive(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_open_drive\n");
		__asm jmp[pAIL_redbook_open_drive]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_pause(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_pause\n");
		__asm jmp[pAIL_redbook_pause]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_play(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_redbook_play\n");
		__asm jmp[pAIL_redbook_play]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_position(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_position\n");
		__asm jmp[pAIL_redbook_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_resume(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_resume\n");
		__asm jmp[pAIL_redbook_resume]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_retract(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_retract\n");
		__asm jmp[pAIL_redbook_retract]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_set_volume_level(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_redbook_set_volume_level\n");
		__asm jmp[pAIL_redbook_set_volume_level]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_status(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_status\n");
		__asm jmp[pAIL_redbook_status]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_stop(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_stop\n");
		__asm jmp[pAIL_redbook_stop]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_track(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_track\n");
		__asm jmp[pAIL_redbook_track]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_track_info(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_redbook_track_info\n");
		__asm jmp[pAIL_redbook_track_info]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_tracks(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_tracks\n");
		__asm jmp[pAIL_redbook_tracks]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_redbook_volume_level(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_redbook_volume_level\n");
		__asm jmp[pAIL_redbook_volume_level]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_3D_EOS_callback(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_3D_EOS_callback\n");
		__asm jmp[pAIL_register_3D_EOS_callback]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_EOB_callback(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_EOB_callback\n");
		__asm jmp[pAIL_register_EOB_callback]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_EOF_callback(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_EOF_callback\n");
		__asm jmp[pAIL_register_EOF_callback]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_EOS_callback(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_EOS_callback\n");
		__asm jmp[pAIL_register_EOS_callback]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_ICA_array(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_ICA_array\n");
		__asm jmp[pAIL_register_ICA_array]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_SOB_callback(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_SOB_callback\n");
		__asm jmp[pAIL_register_SOB_callback]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_beat_callback(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_beat_callback\n");
		__asm jmp[pAIL_register_beat_callback]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_event_callback(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_event_callback\n");
		__asm jmp[pAIL_register_event_callback]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_prefix_callback(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_prefix_callback\n");
		__asm jmp[pAIL_register_prefix_callback]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_sequence_callback(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_sequence_callback\n");
		__asm jmp[pAIL_register_sequence_callback]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_stream_callback(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_stream_callback\n");
		__asm jmp[pAIL_register_stream_callback]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_timbre_callback(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_timbre_callback\n");
		__asm jmp[pAIL_register_timbre_callback]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_timer(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_register_timer\n");
		__asm jmp[pAIL_register_timer]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_register_trigger_callback(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_register_trigger_callback\n");
		__asm jmp[pAIL_register_trigger_callback]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_release_3D_sample_handle(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_release_3D_sample_handle\n");
		__asm jmp[pAIL_release_3D_sample_handle]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_release_all_timers() {
		Com_Printf("^2Miles Debug: AIL_release_all_timers\n");
		__asm jmp[pAIL_release_all_timers]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_release_channel(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_release_channel\n");
		__asm jmp[pAIL_release_channel]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_release_sample_handle(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_release_sample_handle\n");
		__asm jmp[pAIL_release_sample_handle]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_release_sequence_handle(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_release_sequence_handle\n");
		__asm jmp[pAIL_release_sequence_handle]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_release_timer_handle(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_release_timer_handle\n");
		__asm jmp[pAIL_release_timer_handle]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_request_EOB_ASI_reset(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_request_EOB_ASI_reset\n");
		__asm jmp[pAIL_request_EOB_ASI_reset]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_resume_3D_sample(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_resume_3D_sample\n");
		__asm jmp[pAIL_resume_3D_sample]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_resume_sample(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_resume_sample\n");
		__asm jmp[pAIL_resume_sample]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_resume_sequence(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_resume_sequence\n");
		__asm jmp[pAIL_resume_sequence]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_buffer_info(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_sample_buffer_info\n");
		__asm jmp[pAIL_sample_buffer_info]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_buffer_ready(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_sample_buffer_ready\n");
		__asm jmp[pAIL_sample_buffer_ready]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_granularity(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_sample_granularity\n");
		__asm jmp[pAIL_sample_granularity]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_loop_count(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_sample_loop_count\n");
		__asm jmp[pAIL_sample_loop_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_low_pass_cut_off(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_sample_low_pass_cut_off\n");
		__asm jmp[pAIL_sample_low_pass_cut_off]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_ms_position(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_sample_ms_position\n");
		__asm jmp[pAIL_sample_ms_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_playback_rate(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_sample_playback_rate\n");
		__asm jmp[pAIL_sample_playback_rate]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_position(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_sample_position\n");
		__asm jmp[pAIL_sample_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_reverb_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_sample_reverb_levels\n");
		__asm jmp[pAIL_sample_reverb_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_status(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_sample_status\n"); //no more sonic
		__asm jmp[pAIL_sample_status]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_user_data(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_sample_user_data\n");
		__asm jmp[pAIL_sample_user_data]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_volume_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_sample_volume_levels\n");
		__asm jmp[pAIL_sample_volume_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sample_volume_pan(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_sample_volume_pan\n");
		__asm jmp[pAIL_sample_volume_pan]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_send_channel_voice_message(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_send_channel_voice_message\n");
		__asm jmp[pAIL_send_channel_voice_message]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_send_sysex_message(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_send_sysex_message\n");
		__asm jmp[pAIL_send_sysex_message]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sequence_loop_count(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_sequence_loop_count\n");
		__asm jmp[pAIL_sequence_loop_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sequence_ms_position(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_sequence_ms_position\n");
		__asm jmp[pAIL_sequence_ms_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sequence_position(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_sequence_position\n");
		__asm jmp[pAIL_sequence_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sequence_status(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_sequence_status\n");
		__asm jmp[pAIL_sequence_status]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sequence_tempo(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_sequence_tempo\n");
		__asm jmp[pAIL_sequence_tempo]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sequence_user_data(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_sequence_user_data\n");
		__asm jmp[pAIL_sequence_user_data]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_sequence_volume(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_sequence_volume\n");
		__asm jmp[pAIL_sequence_volume]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_serve() {
		Com_Printf("^2Miles Debug: AIL_serve\n");
		__asm jmp[pAIL_serve]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_service_stream(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_service_stream\n");
		__asm jmp[pAIL_service_stream]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_distance_factor(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_distance_factor\n");
		__asm jmp[pAIL_set_3D_distance_factor]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_doppler_factor(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_doppler_factor\n");
		__asm jmp[pAIL_set_3D_doppler_factor]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_orientation(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q, DWORD u, DWORD y) {
		Com_Printf("^2Miles Debug: AIL_set_3D_orientation\n");
		__asm jmp[pAIL_set_3D_orientation]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_position(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_set_3D_position\n");
		__asm jmp[pAIL_set_3D_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_provider_preference(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_3D_provider_preference\n");
		__asm jmp[pAIL_set_3D_provider_preference]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_rolloff_factor(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_rolloff_factor\n");
		__asm jmp[pAIL_set_3D_rolloff_factor]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_room_type(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_room_type\n");
		__asm jmp[pAIL_set_3D_room_type]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_cone(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_cone\n");
		__asm jmp[pAIL_set_3D_sample_cone]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_distances(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_distances\n");
		__asm jmp[pAIL_set_3D_sample_distances]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_effects_level(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_effects_level\n");
		__asm jmp[pAIL_set_3D_sample_effects_level]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_exclusion(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_exclusion\n");
		__asm jmp[pAIL_set_3D_sample_exclusion]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_file(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_file\n");
		__asm jmp[pAIL_set_3D_sample_file]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_info(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_info\n");
		__asm jmp[pAIL_set_3D_sample_info]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_loop_block(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_loop_block\n");
		__asm jmp[pAIL_set_3D_sample_loop_block]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_loop_count(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_loop_count\n");
		__asm jmp[pAIL_set_3D_sample_loop_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_obstruction(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_obstruction\n");
		__asm jmp[pAIL_set_3D_sample_obstruction]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_occlusion(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_occlusion\n");
		__asm jmp[pAIL_set_3D_sample_occlusion]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_offset(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_offset\n");
		__asm jmp[pAIL_set_3D_sample_offset]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_playback_rate(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_playback_rate\n");
		__asm jmp[pAIL_set_3D_sample_playback_rate]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_preference(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_preference\n");
		__asm jmp[pAIL_set_3D_sample_preference]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_sample_volume(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_sample_volume\n");
		__asm jmp[pAIL_set_3D_sample_volume]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_speaker_type(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_3D_speaker_type\n");
		__asm jmp[pAIL_set_3D_speaker_type]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_user_data(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_3D_user_data\n");
		__asm jmp[pAIL_set_3D_user_data]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_velocity(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_set_3D_velocity\n");
		__asm jmp[pAIL_set_3D_velocity]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_3D_velocity_vector(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_set_3D_velocity_vector\n");
		__asm jmp[pAIL_set_3D_velocity_vector]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_DLS_processor(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_DLS_processor\n");
		__asm jmp[pAIL_set_DLS_processor]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_DirectSound_HWND(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_DirectSound_HWND\n");
		__asm jmp[pAIL_set_DirectSound_HWND]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_XMIDI_master_volume(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_XMIDI_master_volume\n");
		__asm jmp[pAIL_set_XMIDI_master_volume]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_digital_driver_processor(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_digital_driver_processor\n");
		__asm jmp[pAIL_set_digital_driver_processor]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_digital_master_reverb(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_set_digital_master_reverb\n");
		__asm jmp[pAIL_set_digital_master_reverb]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_digital_master_reverb_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_digital_master_reverb_levels\n");
		__asm jmp[pAIL_set_digital_master_reverb_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_digital_master_room_type(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_digital_master_room_type\n");
		__asm jmp[pAIL_set_digital_master_room_type]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_digital_master_volume_level(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_digital_master_volume_level\n");
		__asm jmp[pAIL_set_digital_master_volume_level]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_error(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_set_error\n");
		__asm jmp[pAIL_set_error]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_file_async_callbacks(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_set_file_async_callbacks\n");
		__asm jmp[pAIL_set_file_async_callbacks]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_file_callbacks(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_set_file_callbacks\n");
		__asm jmp[pAIL_set_file_callbacks]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_filter_DLS_preference(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_filter_DLS_preference\n");
		__asm jmp[pAIL_set_filter_DLS_preference]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_filter_preference(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_filter_preference\n");
		__asm jmp[pAIL_set_filter_preference]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_filter_sample_preference(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_filter_sample_preference\n");
		__asm jmp[pAIL_set_filter_sample_preference]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_filter_stream_preference(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_filter_stream_preference\n");
		__asm jmp[pAIL_set_filter_stream_preference]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_input_state(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_input_state\n");
		__asm jmp[pAIL_set_input_state]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_named_sample_file(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_set_named_sample_file\n");
		__asm jmp[pAIL_set_named_sample_file]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_preference(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_preference\n");
		__asm jmp[pAIL_set_preference]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_redist_directory(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_set_redist_directory\n");
		__asm jmp[pAIL_set_redist_directory]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_address(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_sample_address\n");
		__asm jmp[pAIL_set_sample_address]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_adpcm_block_size(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_sample_adpcm_block_size\n");
		__asm jmp[pAIL_set_sample_adpcm_block_size]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_file(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_sample_file\n");
		__asm jmp[pAIL_set_sample_file]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_loop_block(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_sample_loop_block\n");
		__asm jmp[pAIL_set_sample_loop_block]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_loop_count(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_sample_loop_count\n");
		__asm jmp[pAIL_set_sample_loop_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_low_pass_cut_off(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_sample_low_pass_cut_off\n");
		__asm jmp[pAIL_set_sample_low_pass_cut_off]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_ms_position(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_sample_ms_position\n");
		__asm jmp[pAIL_set_sample_ms_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_playback_rate(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_sample_playback_rate\n");
		__asm jmp[pAIL_set_sample_playback_rate]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_position(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_sample_position\n");
		__asm jmp[pAIL_set_sample_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_processor(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_sample_processor\n");
		__asm jmp[pAIL_set_sample_processor]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_reverb_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_sample_reverb_levels\n");
		__asm jmp[pAIL_set_sample_reverb_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_type(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_sample_type\n");
		__asm jmp[pAIL_set_sample_type]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_user_data(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_sample_user_data\n");
		__asm jmp[pAIL_set_sample_user_data]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_volume_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_sample_volume_levels\n");
		__asm jmp[pAIL_set_sample_volume_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sample_volume_pan(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_sample_volume_pan\n");
		__asm jmp[pAIL_set_sample_volume_pan]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sequence_loop_count(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_sequence_loop_count\n");
		__asm jmp[pAIL_set_sequence_loop_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sequence_ms_position(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_sequence_ms_position\n");
		__asm jmp[pAIL_set_sequence_ms_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sequence_tempo(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_sequence_tempo\n");
		__asm jmp[pAIL_set_sequence_tempo]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sequence_user_data(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_sequence_user_data\n");
		__asm jmp[pAIL_set_sequence_user_data]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_sequence_volume(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_sequence_volume\n");
		__asm jmp[pAIL_set_sequence_volume]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_stream_loop_block(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_stream_loop_block\n");
		__asm jmp[pAIL_set_stream_loop_block]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_stream_loop_count(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_stream_loop_count\n");
		__asm jmp[pAIL_set_stream_loop_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_stream_low_pass_cut_off(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_stream_low_pass_cut_off\n");
		__asm jmp[pAIL_set_stream_low_pass_cut_off]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_stream_ms_position(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_stream_ms_position\n");
		__asm jmp[pAIL_set_stream_ms_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_stream_playback_rate(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_stream_playback_rate\n");
		__asm jmp[pAIL_set_stream_playback_rate]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_stream_position(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_stream_position\n");
		__asm jmp[pAIL_set_stream_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_stream_processor(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_stream_processor\n");
		__asm jmp[pAIL_set_stream_processor]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_stream_reverb_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_stream_reverb_levels\n");
		__asm jmp[pAIL_set_stream_reverb_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_stream_user_data(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_stream_user_data\n");
		__asm jmp[pAIL_set_stream_user_data]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_stream_volume_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_set_stream_volume_levels\n");
		__asm jmp[pAIL_set_stream_volume_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_stream_volume_pan(DWORD a, DWORD e, DWORD i) {
		//Com_Printf("^2Miles Debug: AIL_set_stream_volume_pan\n"); //gotta go fast
		__asm jmp[pAIL_set_stream_volume_pan]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_timer_divisor(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_timer_divisor\n");
		__asm jmp[pAIL_set_timer_divisor]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_timer_frequency(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_timer_frequency\n");
		__asm jmp[pAIL_set_timer_frequency]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_timer_period(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_timer_period\n");
		__asm jmp[pAIL_set_timer_period]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_set_timer_user(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_set_timer_user\n");
		__asm jmp[pAIL_set_timer_user]
	}
	MSS_DLL_EXPORT void WINAPI AIL_shutdown() {
		//Com_Printf("^2Miles Debug: AIL_shutdown\n");
		//__asm jmp[pAIL_shutdown]
		void(WINAPI*o)() = (void(WINAPI*)())pAIL_shutdown;
		o();
		extern bool bClosing;
		if (!bClosing)
			return;

		void MSS32_Unload();
		MSS32_Unload();

	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_size_processed_digital_audio(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_size_processed_digital_audio\n");
		__asm jmp[pAIL_size_processed_digital_audio]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_start_3D_sample(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_start_3D_sample\n");
		__asm jmp[pAIL_start_3D_sample]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_start_all_timers() {
		Com_Printf("^2Miles Debug: AIL_start_all_timers\n");
		__asm jmp[pAIL_start_all_timers]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_start_sample(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_start_sample\n");
		__asm jmp[pAIL_start_sample]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_start_sequence(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_start_sequence\n");
		__asm jmp[pAIL_start_sequence]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_start_stream(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_start_stream\n");
		__asm jmp[pAIL_start_stream]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_start_timer(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_start_timer\n");
		__asm jmp[pAIL_start_timer]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_startup() {
		Com_Printf("^2Miles Debug: AIL_startup\n");
		__asm jmp[pAIL_startup]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stop_3D_sample(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_stop_3D_sample\n");
		__asm jmp[pAIL_stop_3D_sample]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stop_all_timers() {
		Com_Printf("^2Miles Debug: AIL_stop_all_timers\n");
		__asm jmp[pAIL_stop_all_timers]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stop_sample(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_stop_sample\n");
		__asm jmp[pAIL_stop_sample]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stop_sequence(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_stop_sequence\n");
		__asm jmp[pAIL_stop_sequence]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stop_timer(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_stop_timer\n");
		__asm jmp[pAIL_stop_timer]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stream_info(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: AIL_stream_info\n");
		__asm jmp[pAIL_stream_info]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stream_loop_count(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_stream_loop_count\n");
		__asm jmp[pAIL_stream_loop_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stream_low_pass_cut_off(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_stream_low_pass_cut_off\n");
		__asm jmp[pAIL_stream_low_pass_cut_off]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stream_ms_position(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_stream_ms_position\n");
		__asm jmp[pAIL_stream_ms_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stream_playback_rate(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_stream_playback_rate\n");
		__asm jmp[pAIL_stream_playback_rate]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stream_position(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_stream_position\n");
		__asm jmp[pAIL_stream_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stream_reverb_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_stream_reverb_levels\n");
		__asm jmp[pAIL_stream_reverb_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stream_status(DWORD a) {
		//Com_Printf("^2Miles Debug: AIL_stream_status\n"); //sonics
		__asm jmp[pAIL_stream_status]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stream_user_data(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_stream_user_data\n");
		__asm jmp[pAIL_stream_user_data]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stream_volume_levels(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_stream_volume_levels\n");
		__asm jmp[pAIL_stream_volume_levels]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_stream_volume_pan(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: AIL_stream_volume_pan\n");
		__asm jmp[pAIL_stream_volume_pan]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_true_sequence_channel(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_true_sequence_channel\n");
		__asm jmp[pAIL_true_sequence_channel]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_unlock() {
		Com_Printf("^2Miles Debug: AIL_unlock\n");
		__asm jmp[pAIL_unlock]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_unlock_mutex() {
		Com_Printf("^2Miles Debug: AIL_unlock_mutex\n");
		__asm jmp[pAIL_unlock_mutex]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_update_3D_position(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: AIL_update_3D_position\n");
		__asm jmp[pAIL_update_3D_position]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_us_count() {
		Com_Printf("^2Miles Debug: AIL_us_count\n");
		__asm jmp[pAIL_us_count]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_waveOutClose(DWORD a) {
		Com_Printf("^2Miles Debug: AIL_waveOutClose\n");
		__asm jmp[pAIL_waveOutClose]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI AIL_waveOutOpen(DWORD a, DWORD e, DWORD i, DWORD m) {
		Com_Printf("^2Miles Debug: AIL_waveOutOpen\n");
		__asm jmp[pAIL_waveOutOpen]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI DLSMSSGetCPU(DWORD a) {
		Com_Printf("^2Miles Debug: DLSMSSGetCPU\n");
		__asm jmp[pDLSMSSGetCPU]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI MIX_RIB_MAIN(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: MIX_RIB_MAIN\n");
		__asm jmp[pMIX_RIB_MAIN]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI RIB_enumerate_providers(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: RIB_enumerate_providers\n");
		__asm jmp[pRIB_enumerate_providers]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI RIB_find_file_dec_provider(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: RIB_find_file_dec_provider\n");
		__asm jmp[pRIB_find_file_dec_provider]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI RIB_find_files_provider(DWORD a, DWORD e, DWORD i, DWORD m, DWORD q) {
		Com_Printf("^2Miles Debug: RIB_find_files_provider\n");
		__asm jmp[pRIB_find_files_provider]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI RIB_find_provider(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: RIB_find_provider\n");
		__asm jmp[pRIB_find_provider]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI RIB_load_application_providers(DWORD a) {
		Com_Printf("^2Miles Debug: RIB_load_application_providers\n");
		__asm jmp[pRIB_load_application_providers]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI RIB_load_static_provider_library(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: RIB_load_static_provider_library\n");
		__asm jmp[pRIB_load_static_provider_library]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI RIB_provider_system_data(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: RIB_provider_system_data\n");
		__asm jmp[pRIB_provider_system_data]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI RIB_provider_user_data(DWORD a, DWORD e) {
		Com_Printf("^2Miles Debug: RIB_provider_user_data\n");
		__asm jmp[pRIB_provider_user_data]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI RIB_set_provider_system_data(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: RIB_set_provider_system_data\n");
		__asm jmp[pRIB_set_provider_system_data]
	}
	__declspec(naked) MSS_DLL_EXPORT void WINAPI RIB_set_provider_user_data(DWORD a, DWORD e, DWORD i) {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pRIB_set_provider_user_data]
	}
	__declspec(naked) MSS_DLL_EXPORT void stream_background() {
		Com_Printf("^2Miles Debug: RIB_set_provider_user_data\n");
		__asm jmp[pstream_background]
	}


}

extern "C" void MSS32_Unload() {
	if (hMSS != nullptr)
		FreeLibrary(hMSS);
	//MsgBox("mss32 unloaded");
}

bool miles32_loaded = false;

void MSS32_Hook() {
	hMSS = nullptr;

	hMSS = LoadLibraryA("miles32.dll");

	if (!hMSS) {
		MessageBoxA(NULL, "Failed to load miles32.dll", __TITLE, MB_OK | MB_ICONERROR);
		Com_Quit_f();
		return;
	}

	pAIL_debug_printf = GetProcAddress(hMSS, "AIL_debug_printf");
	pAIL_sprintf = GetProcAddress(hMSS, "AIL_sprintf");
	pDLSClose = GetProcAddress(hMSS, "DLSClose");
	pDLSCompactMemory = GetProcAddress(hMSS, "DLSCompactMemory");
	pDLSGetInfo = GetProcAddress(hMSS, "DLSGetInfo");
	pDLSLoadFile = GetProcAddress(hMSS, "DLSLoadFile");
	pDLSLoadMemFile = GetProcAddress(hMSS, "DLSLoadMemFile");
	pDLSMSSOpen = GetProcAddress(hMSS, "DLSMSSOpen");
	pDLSSetAttribute = GetProcAddress(hMSS, "DLSSetAttribute");
	pDLSUnloadAll = GetProcAddress(hMSS, "DLSUnloadAll");
	pDLSUnloadFile = GetProcAddress(hMSS, "DLSUnloadFile");
	pRIB_alloc_provider_handle = GetProcAddress(hMSS, "RIB_alloc_provider_handle");
	pRIB_enumerate_interface = GetProcAddress(hMSS, "RIB_enumerate_interface");
	pRIB_error = GetProcAddress(hMSS, "RIB_error");
	pRIB_find_file_provider = GetProcAddress(hMSS, "RIB_find_file_provider");
	pRIB_free_provider_handle = GetProcAddress(hMSS, "RIB_free_provider_handle");
	pRIB_free_provider_library = GetProcAddress(hMSS, "RIB_free_provider_library");
	pRIB_load_provider_library = GetProcAddress(hMSS, "RIB_load_provider_library");
	pRIB_register_interface = GetProcAddress(hMSS, "RIB_register_interface");
	pRIB_request_interface = GetProcAddress(hMSS, "RIB_request_interface");
	pRIB_request_interface_entry = GetProcAddress(hMSS, "RIB_request_interface_entry");
	pRIB_type_string = GetProcAddress(hMSS, "RIB_type_string");
	pRIB_unregister_interface = GetProcAddress(hMSS, "RIB_unregister_interface");
	pAIL_3D_distance_factor = GetProcAddress(hMSS, "_AIL_3D_distance_factor@4");
	pAIL_3D_doppler_factor = GetProcAddress(hMSS, "_AIL_3D_doppler_factor@4");
	pAIL_3D_orientation = GetProcAddress(hMSS, "_AIL_3D_orientation@28");
	pAIL_3D_position = GetProcAddress(hMSS, "_AIL_3D_position@16");
	pAIL_3D_provider_attribute = GetProcAddress(hMSS, "_AIL_3D_provider_attribute@12");
	pAIL_3D_rolloff_factor = GetProcAddress(hMSS, "_AIL_3D_rolloff_factor@4");
	pAIL_3D_room_type = GetProcAddress(hMSS, "_AIL_3D_room_type@4");
	pAIL_3D_sample_attribute = GetProcAddress(hMSS, "_AIL_3D_sample_attribute@12");
	pAIL_3D_sample_cone = GetProcAddress(hMSS, "_AIL_3D_sample_cone@16");
	pAIL_3D_sample_distances = GetProcAddress(hMSS, "_AIL_3D_sample_distances@12");
	pAIL_3D_sample_effects_level = GetProcAddress(hMSS, "_AIL_3D_sample_effects_level@4");
	pAIL_3D_sample_exclusion = GetProcAddress(hMSS, "_AIL_3D_sample_exclusion@4");
	pAIL_3D_sample_length = GetProcAddress(hMSS, "_AIL_3D_sample_length@4");
	pAIL_3D_sample_loop_count = GetProcAddress(hMSS, "_AIL_3D_sample_loop_count@4");
	pAIL_3D_sample_obstruction = GetProcAddress(hMSS, "_AIL_3D_sample_obstruction@4");
	pAIL_3D_sample_occlusion = GetProcAddress(hMSS, "_AIL_3D_sample_occlusion@4");
	pAIL_3D_sample_offset = GetProcAddress(hMSS, "_AIL_3D_sample_offset@4");
	pAIL_3D_sample_playback_rate = GetProcAddress(hMSS, "_AIL_3D_sample_playback_rate@4");
	pAIL_3D_sample_status = GetProcAddress(hMSS, "_AIL_3D_sample_status@4");
	pAIL_3D_sample_volume = GetProcAddress(hMSS, "_AIL_3D_sample_volume@4");
	pAIL_3D_speaker_type = GetProcAddress(hMSS, "_AIL_3D_speaker_type@4");
	pAIL_3D_user_data = GetProcAddress(hMSS, "_AIL_3D_user_data@8");
	pAIL_3D_velocity = GetProcAddress(hMSS, "_AIL_3D_velocity@16");
	pAIL_DLS_close = GetProcAddress(hMSS, "_AIL_DLS_close@8");
	pAIL_DLS_compact = GetProcAddress(hMSS, "_AIL_DLS_compact@4");
	pAIL_DLS_get_info = GetProcAddress(hMSS, "_AIL_DLS_get_info@12");
	pAIL_DLS_get_reverb_levels = GetProcAddress(hMSS, "_AIL_DLS_get_reverb_levels@12");
	pAIL_DLS_load_file = GetProcAddress(hMSS, "_AIL_DLS_load_file@12");
	pAIL_DLS_load_memory = GetProcAddress(hMSS, "_AIL_DLS_load_memory@12");
	pAIL_DLS_open = GetProcAddress(hMSS, "_AIL_DLS_open@28");
	pAIL_DLS_set_reverb_levels = GetProcAddress(hMSS, "_AIL_DLS_set_reverb_levels@12");
	pAIL_DLS_unload = GetProcAddress(hMSS, "_AIL_DLS_unload@8");
	pAIL_HWND = GetProcAddress(hMSS, "_AIL_HWND@0");
	pAIL_MIDI_handle_reacquire = GetProcAddress(hMSS, "_AIL_MIDI_handle_reacquire@4");
	pAIL_MIDI_handle_release = GetProcAddress(hMSS, "_AIL_MIDI_handle_release@4");
	pAIL_MIDI_to_XMI = GetProcAddress(hMSS, "_AIL_MIDI_to_XMI@20");
	pAIL_MMX_available = GetProcAddress(hMSS, "_AIL_MMX_available@0");
	pAIL_WAV_file_write = GetProcAddress(hMSS, "_AIL_WAV_file_write@20");
	pAIL_WAV_info = GetProcAddress(hMSS, "_AIL_WAV_info@8");
	pAIL_XMIDI_master_volume = GetProcAddress(hMSS, "_AIL_XMIDI_master_volume@4");
	pAIL_active_3D_sample_count = GetProcAddress(hMSS, "_AIL_active_3D_sample_count@4");
	pAIL_active_sample_count = GetProcAddress(hMSS, "_AIL_active_sample_count@4");
	pAIL_active_sequence_count = GetProcAddress(hMSS, "_AIL_active_sequence_count@4");
	pAIL_allocate_3D_sample_handle = GetProcAddress(hMSS, "_AIL_allocate_3D_sample_handle@4");
	pAIL_allocate_file_sample = GetProcAddress(hMSS, "_AIL_allocate_file_sample@12");
	pAIL_allocate_sample_handle = GetProcAddress(hMSS, "_AIL_allocate_sample_handle@4");
	pAIL_allocate_sequence_handle = GetProcAddress(hMSS, "_AIL_allocate_sequence_handle@4");
	pAIL_auto_service_stream = GetProcAddress(hMSS, "_AIL_auto_service_stream@8");
	pAIL_auto_update_3D_position = GetProcAddress(hMSS, "_AIL_auto_update_3D_position@8");
	pAIL_background = GetProcAddress(hMSS, "_AIL_background@0");
	pAIL_branch_index = GetProcAddress(hMSS, "_AIL_branch_index@8");
	pAIL_channel_notes = GetProcAddress(hMSS, "_AIL_channel_notes@8");
	pAIL_close_3D_listener = GetProcAddress(hMSS, "_AIL_close_3D_listener@4");
	pAIL_close_3D_object = GetProcAddress(hMSS, "_AIL_close_3D_object@4");
	pAIL_close_3D_provider = GetProcAddress(hMSS, "_AIL_close_3D_provider@4");
	pAIL_close_XMIDI_driver = GetProcAddress(hMSS, "_AIL_close_XMIDI_driver@4");
	pAIL_close_digital_driver = GetProcAddress(hMSS, "_AIL_close_digital_driver@4");
	pAIL_close_filter = GetProcAddress(hMSS, "_AIL_close_filter@4");
	pAIL_close_input = GetProcAddress(hMSS, "_AIL_close_input@4");
	pAIL_close_stream = GetProcAddress(hMSS, "_AIL_close_stream@4");
	pAIL_compress_ADPCM = GetProcAddress(hMSS, "_AIL_compress_ADPCM@12");
	pAIL_compress_ASI = GetProcAddress(hMSS, "_AIL_compress_ASI@20");
	pAIL_compress_DLS = GetProcAddress(hMSS, "_AIL_compress_DLS@20");
	pAIL_controller_value = GetProcAddress(hMSS, "_AIL_controller_value@12");
	pAIL_create_wave_synthesizer = GetProcAddress(hMSS, "_AIL_create_wave_synthesizer@16");
	pAIL_decompress_ADPCM = GetProcAddress(hMSS, "_AIL_decompress_ADPCM@12");
	pAIL_decompress_ASI = GetProcAddress(hMSS, "_AIL_decompress_ASI@24");
	pAIL_delay = GetProcAddress(hMSS, "_AIL_delay@4");
	pAIL_destroy_wave_synthesizer = GetProcAddress(hMSS, "_AIL_destroy_wave_synthesizer@4");
	pAIL_digital_CPU_percent = GetProcAddress(hMSS, "_AIL_digital_CPU_percent@4");
	pAIL_digital_configuration = GetProcAddress(hMSS, "_AIL_digital_configuration@16");
	pAIL_digital_handle_reacquire = GetProcAddress(hMSS, "_AIL_digital_handle_reacquire@4");
	pAIL_digital_handle_release = GetProcAddress(hMSS, "_AIL_digital_handle_release@4");
	pAIL_digital_latency = GetProcAddress(hMSS, "_AIL_digital_latency@4");
	pAIL_digital_master_reverb = GetProcAddress(hMSS, "_AIL_digital_master_reverb@16");
	pAIL_digital_master_reverb_levels = GetProcAddress(hMSS, "_AIL_digital_master_reverb_levels@12");
	pAIL_digital_master_volume_level = GetProcAddress(hMSS, "_AIL_digital_master_volume_level@4");
	pAIL_end_3D_sample = GetProcAddress(hMSS, "_AIL_end_3D_sample@4");
	pAIL_end_sample = GetProcAddress(hMSS, "_AIL_end_sample@4");
	pAIL_end_sequence = GetProcAddress(hMSS, "_AIL_end_sequence@4");
	pAIL_enumerate_3D_provider_attributes = GetProcAddress(hMSS, "_AIL_enumerate_3D_provider_attributes@12");
	pAIL_enumerate_3D_providers = GetProcAddress(hMSS, "_AIL_enumerate_3D_providers@12");
	pAIL_enumerate_3D_sample_attributes = GetProcAddress(hMSS, "_AIL_enumerate_3D_sample_attributes@12");
	pAIL_enumerate_filter_attributes = GetProcAddress(hMSS, "_AIL_enumerate_filter_attributes@12");
	pAIL_enumerate_filter_sample_attributes = GetProcAddress(hMSS, "_AIL_enumerate_filter_sample_attributes@12");
	pAIL_enumerate_filters = GetProcAddress(hMSS, "_AIL_enumerate_filters@12");
	pAIL_extract_DLS = GetProcAddress(hMSS, "_AIL_extract_DLS@28");
	pAIL_file_error = GetProcAddress(hMSS, "_AIL_file_error@0");
	pAIL_file_read = GetProcAddress(hMSS, "_AIL_file_read@8");
	pAIL_file_size = GetProcAddress(hMSS, "_AIL_file_size@4");
	pAIL_file_type = GetProcAddress(hMSS, "_AIL_file_type@8");
	pAIL_file_write = GetProcAddress(hMSS, "_AIL_file_write@12");
	pAIL_filter_DLS_attribute = GetProcAddress(hMSS, "_AIL_filter_DLS_attribute@12");
	pAIL_filter_DLS_with_XMI = GetProcAddress(hMSS, "_AIL_filter_DLS_with_XMI@24");
	pAIL_filter_attribute = GetProcAddress(hMSS, "_AIL_filter_attribute@12");
	pAIL_filter_sample_attribute = GetProcAddress(hMSS, "_AIL_filter_sample_attribute@12");
	pAIL_filter_stream_attribute = GetProcAddress(hMSS, "_AIL_filter_stream_attribute@12");
	pAIL_find_DLS = GetProcAddress(hMSS, "_AIL_find_DLS@24");
	pAIL_get_DirectSound_info = GetProcAddress(hMSS, "_AIL_get_DirectSound_info@12");
	pAIL_get_input_info = GetProcAddress(hMSS, "_AIL_get_input_info@4");
	pAIL_get_preference = GetProcAddress(hMSS, "_AIL_get_preference@4");
	pAIL_get_timer_highest_delay = GetProcAddress(hMSS, "_AIL_get_timer_highest_delay@0");
	pAIL_init_sample = GetProcAddress(hMSS, "_AIL_init_sample@4");
	pAIL_init_sequence = GetProcAddress(hMSS, "_AIL_init_sequence@12");
	pAIL_last_error = GetProcAddress(hMSS, "_AIL_last_error@0");
	pAIL_list_DLS = GetProcAddress(hMSS, "_AIL_list_DLS@20");
	pAIL_list_MIDI = GetProcAddress(hMSS, "_AIL_list_MIDI@20");
	pAIL_load_sample_buffer = GetProcAddress(hMSS, "_AIL_load_sample_buffer@16");
	pAIL_lock = GetProcAddress(hMSS, "_AIL_lock@0");
	pAIL_lock_channel = GetProcAddress(hMSS, "_AIL_lock_channel@4");
	pAIL_lock_mutex = GetProcAddress(hMSS, "_AIL_lock_mutex@0");
	pAIL_map_sequence_channel = GetProcAddress(hMSS, "_AIL_map_sequence_channel@12");
	pAIL_mem_alloc_lock = GetProcAddress(hMSS, "_AIL_mem_alloc_lock@4");
	pAIL_mem_free_lock = GetProcAddress(hMSS, "_AIL_mem_free_lock@4");
	pAIL_mem_use_free = GetProcAddress(hMSS, "_AIL_mem_use_free@4");
	pAIL_mem_use_malloc = GetProcAddress(hMSS, "_AIL_mem_use_malloc@4");
	pAIL_merge_DLS_with_XMI = GetProcAddress(hMSS, "_AIL_merge_DLS_with_XMI@16");
	pAIL_midiOutClose = GetProcAddress(hMSS, "_AIL_midiOutClose@4");
	pAIL_midiOutOpen = GetProcAddress(hMSS, "_AIL_midiOutOpen@12");
	pAIL_minimum_sample_buffer_size = GetProcAddress(hMSS, "_AIL_minimum_sample_buffer_size@12");
	pAIL_ms_count = GetProcAddress(hMSS, "_AIL_ms_count@0");
	pAIL_open_3D_listener = GetProcAddress(hMSS, "_AIL_open_3D_listener@4");
	pAIL_open_3D_object = GetProcAddress(hMSS, "_AIL_open_3D_object@4");
	pAIL_open_3D_provider = GetProcAddress(hMSS, "_AIL_open_3D_provider@4");
	pAIL_open_XMIDI_driver = GetProcAddress(hMSS, "_AIL_open_XMIDI_driver@4");
	pAIL_open_digital_driver = GetProcAddress(hMSS, "_AIL_open_digital_driver@16");
	pAIL_open_filter = GetProcAddress(hMSS, "_AIL_open_filter@8");
	pAIL_open_input = GetProcAddress(hMSS, "_AIL_open_input@4");
	pAIL_open_stream = GetProcAddress(hMSS, "_AIL_open_stream@12");
	pAIL_pause_stream = GetProcAddress(hMSS, "_AIL_pause_stream@8");
	pAIL_primary_digital_driver = GetProcAddress(hMSS, "_AIL_primary_digital_driver@4");
	pAIL_process_digital_audio = GetProcAddress(hMSS, "_AIL_process_digital_audio@24");
	pAIL_quick_copy = GetProcAddress(hMSS, "_AIL_quick_copy@4");
	pAIL_quick_halt = GetProcAddress(hMSS, "_AIL_quick_halt@4");
	pAIL_quick_handles = GetProcAddress(hMSS, "_AIL_quick_handles@12");
	pAIL_quick_load = GetProcAddress(hMSS, "_AIL_quick_load@4");
	pAIL_quick_load_and_play = GetProcAddress(hMSS, "_AIL_quick_load_and_play@12");
	pAIL_quick_load_mem = GetProcAddress(hMSS, "_AIL_quick_load_mem@8");
	pAIL_quick_ms_length = GetProcAddress(hMSS, "_AIL_quick_ms_length@4");
	pAIL_quick_ms_position = GetProcAddress(hMSS, "_AIL_quick_ms_position@4");
	pAIL_quick_play = GetProcAddress(hMSS, "_AIL_quick_play@8");
	pAIL_quick_set_low_pass_cut_off = GetProcAddress(hMSS, "_AIL_quick_set_low_pass_cut_off@8");
	pAIL_quick_set_ms_position = GetProcAddress(hMSS, "_AIL_quick_set_ms_position@8");
	pAIL_quick_set_reverb_levels = GetProcAddress(hMSS, "_AIL_quick_set_reverb_levels@12");
	pAIL_quick_set_speed = GetProcAddress(hMSS, "_AIL_quick_set_speed@8");
	pAIL_quick_set_volume = GetProcAddress(hMSS, "_AIL_quick_set_volume@12");
	pAIL_quick_shutdown = GetProcAddress(hMSS, "_AIL_quick_shutdown@0");
	pAIL_quick_startup = GetProcAddress(hMSS, "_AIL_quick_startup@20");
	pAIL_quick_status = GetProcAddress(hMSS, "_AIL_quick_status@4");
	pAIL_quick_type = GetProcAddress(hMSS, "_AIL_quick_type@4");
	pAIL_quick_unload = GetProcAddress(hMSS, "_AIL_quick_unload@4");
	pAIL_redbook_close = GetProcAddress(hMSS, "_AIL_redbook_close@4");
	pAIL_redbook_eject = GetProcAddress(hMSS, "_AIL_redbook_eject@4");
	pAIL_redbook_id = GetProcAddress(hMSS, "_AIL_redbook_id@4");
	pAIL_redbook_open = GetProcAddress(hMSS, "_AIL_redbook_open@4");
	pAIL_redbook_open_drive = GetProcAddress(hMSS, "_AIL_redbook_open_drive@4");
	pAIL_redbook_pause = GetProcAddress(hMSS, "_AIL_redbook_pause@4");
	pAIL_redbook_play = GetProcAddress(hMSS, "_AIL_redbook_play@12");
	pAIL_redbook_position = GetProcAddress(hMSS, "_AIL_redbook_position@4");
	pAIL_redbook_resume = GetProcAddress(hMSS, "_AIL_redbook_resume@4");
	pAIL_redbook_retract = GetProcAddress(hMSS, "_AIL_redbook_retract@4");
	pAIL_redbook_set_volume_level = GetProcAddress(hMSS, "_AIL_redbook_set_volume_level@8");
	pAIL_redbook_status = GetProcAddress(hMSS, "_AIL_redbook_status@4");
	pAIL_redbook_stop = GetProcAddress(hMSS, "_AIL_redbook_stop@4");
	pAIL_redbook_track = GetProcAddress(hMSS, "_AIL_redbook_track@4");
	pAIL_redbook_track_info = GetProcAddress(hMSS, "_AIL_redbook_track_info@16");
	pAIL_redbook_tracks = GetProcAddress(hMSS, "_AIL_redbook_tracks@4");
	pAIL_redbook_volume_level = GetProcAddress(hMSS, "_AIL_redbook_volume_level@4");
	pAIL_register_3D_EOS_callback = GetProcAddress(hMSS, "_AIL_register_3D_EOS_callback@8");
	pAIL_register_EOB_callback = GetProcAddress(hMSS, "_AIL_register_EOB_callback@8");
	pAIL_register_EOF_callback = GetProcAddress(hMSS, "_AIL_register_EOF_callback@8");
	pAIL_register_EOS_callback = GetProcAddress(hMSS, "_AIL_register_EOS_callback@8");
	pAIL_register_ICA_array = GetProcAddress(hMSS, "_AIL_register_ICA_array@8");
	pAIL_register_SOB_callback = GetProcAddress(hMSS, "_AIL_register_SOB_callback@8");
	pAIL_register_beat_callback = GetProcAddress(hMSS, "_AIL_register_beat_callback@8");
	pAIL_register_event_callback = GetProcAddress(hMSS, "_AIL_register_event_callback@8");
	pAIL_register_prefix_callback = GetProcAddress(hMSS, "_AIL_register_prefix_callback@8");
	pAIL_register_sequence_callback = GetProcAddress(hMSS, "_AIL_register_sequence_callback@8");
	pAIL_register_stream_callback = GetProcAddress(hMSS, "_AIL_register_stream_callback@8");
	pAIL_register_timbre_callback = GetProcAddress(hMSS, "_AIL_register_timbre_callback@8");
	pAIL_register_timer = GetProcAddress(hMSS, "_AIL_register_timer@4");
	pAIL_register_trigger_callback = GetProcAddress(hMSS, "_AIL_register_trigger_callback@8");
	pAIL_release_3D_sample_handle = GetProcAddress(hMSS, "_AIL_release_3D_sample_handle@4");
	pAIL_release_all_timers = GetProcAddress(hMSS, "_AIL_release_all_timers@0");
	pAIL_release_channel = GetProcAddress(hMSS, "_AIL_release_channel@8");
	pAIL_release_sample_handle = GetProcAddress(hMSS, "_AIL_release_sample_handle@4");
	pAIL_release_sequence_handle = GetProcAddress(hMSS, "_AIL_release_sequence_handle@4");
	pAIL_release_timer_handle = GetProcAddress(hMSS, "_AIL_release_timer_handle@4");
	pAIL_request_EOB_ASI_reset = GetProcAddress(hMSS, "_AIL_request_EOB_ASI_reset@8");
	pAIL_resume_3D_sample = GetProcAddress(hMSS, "_AIL_resume_3D_sample@4");
	pAIL_resume_sample = GetProcAddress(hMSS, "_AIL_resume_sample@4");
	pAIL_resume_sequence = GetProcAddress(hMSS, "_AIL_resume_sequence@4");
	pAIL_sample_buffer_info = GetProcAddress(hMSS, "_AIL_sample_buffer_info@20");
	pAIL_sample_buffer_ready = GetProcAddress(hMSS, "_AIL_sample_buffer_ready@4");
	pAIL_sample_granularity = GetProcAddress(hMSS, "_AIL_sample_granularity@4");
	pAIL_sample_loop_count = GetProcAddress(hMSS, "_AIL_sample_loop_count@4");
	pAIL_sample_low_pass_cut_off = GetProcAddress(hMSS, "_AIL_sample_low_pass_cut_off@4");
	pAIL_sample_ms_position = GetProcAddress(hMSS, "_AIL_sample_ms_position@12");
	pAIL_sample_playback_rate = GetProcAddress(hMSS, "_AIL_sample_playback_rate@4");
	pAIL_sample_position = GetProcAddress(hMSS, "_AIL_sample_position@4");
	pAIL_sample_reverb_levels = GetProcAddress(hMSS, "_AIL_sample_reverb_levels@12");
	pAIL_sample_status = GetProcAddress(hMSS, "_AIL_sample_status@4");
	pAIL_sample_user_data = GetProcAddress(hMSS, "_AIL_sample_user_data@8");
	pAIL_sample_volume_levels = GetProcAddress(hMSS, "_AIL_sample_volume_levels@12");
	pAIL_sample_volume_pan = GetProcAddress(hMSS, "_AIL_sample_volume_pan@12");
	pAIL_send_channel_voice_message = GetProcAddress(hMSS, "_AIL_send_channel_voice_message@20");
	pAIL_send_sysex_message = GetProcAddress(hMSS, "_AIL_send_sysex_message@8");
	pAIL_sequence_loop_count = GetProcAddress(hMSS, "_AIL_sequence_loop_count@4");
	pAIL_sequence_ms_position = GetProcAddress(hMSS, "_AIL_sequence_ms_position@12");
	pAIL_sequence_position = GetProcAddress(hMSS, "_AIL_sequence_position@12");
	pAIL_sequence_status = GetProcAddress(hMSS, "_AIL_sequence_status@4");
	pAIL_sequence_tempo = GetProcAddress(hMSS, "_AIL_sequence_tempo@4");
	pAIL_sequence_user_data = GetProcAddress(hMSS, "_AIL_sequence_user_data@8");
	pAIL_sequence_volume = GetProcAddress(hMSS, "_AIL_sequence_volume@4");
	pAIL_serve = GetProcAddress(hMSS, "_AIL_serve@0");
	pAIL_service_stream = GetProcAddress(hMSS, "_AIL_service_stream@8");
	pAIL_set_3D_distance_factor = GetProcAddress(hMSS, "_AIL_set_3D_distance_factor@8");
	pAIL_set_3D_doppler_factor = GetProcAddress(hMSS, "_AIL_set_3D_doppler_factor@8");
	pAIL_set_3D_orientation = GetProcAddress(hMSS, "_AIL_set_3D_orientation@28");
	pAIL_set_3D_position = GetProcAddress(hMSS, "_AIL_set_3D_position@16");
	pAIL_set_3D_provider_preference = GetProcAddress(hMSS, "_AIL_set_3D_provider_preference@12");
	pAIL_set_3D_rolloff_factor = GetProcAddress(hMSS, "_AIL_set_3D_rolloff_factor@8");
	pAIL_set_3D_room_type = GetProcAddress(hMSS, "_AIL_set_3D_room_type@8");
	pAIL_set_3D_sample_cone = GetProcAddress(hMSS, "_AIL_set_3D_sample_cone@16");
	pAIL_set_3D_sample_distances = GetProcAddress(hMSS, "_AIL_set_3D_sample_distances@12");
	pAIL_set_3D_sample_effects_level = GetProcAddress(hMSS, "_AIL_set_3D_sample_effects_level@8");
	pAIL_set_3D_sample_exclusion = GetProcAddress(hMSS, "_AIL_set_3D_sample_exclusion@8");
	pAIL_set_3D_sample_file = GetProcAddress(hMSS, "_AIL_set_3D_sample_file@8");
	pAIL_set_3D_sample_info = GetProcAddress(hMSS, "_AIL_set_3D_sample_info@8");
	pAIL_set_3D_sample_loop_block = GetProcAddress(hMSS, "_AIL_set_3D_sample_loop_block@12");
	pAIL_set_3D_sample_loop_count = GetProcAddress(hMSS, "_AIL_set_3D_sample_loop_count@8");
	pAIL_set_3D_sample_obstruction = GetProcAddress(hMSS, "_AIL_set_3D_sample_obstruction@8");
	pAIL_set_3D_sample_occlusion = GetProcAddress(hMSS, "_AIL_set_3D_sample_occlusion@8");
	pAIL_set_3D_sample_offset = GetProcAddress(hMSS, "_AIL_set_3D_sample_offset@8");
	pAIL_set_3D_sample_playback_rate = GetProcAddress(hMSS, "_AIL_set_3D_sample_playback_rate@8");
	pAIL_set_3D_sample_preference = GetProcAddress(hMSS, "_AIL_set_3D_sample_preference@12");
	pAIL_set_3D_sample_volume = GetProcAddress(hMSS, "_AIL_set_3D_sample_volume@8");
	pAIL_set_3D_speaker_type = GetProcAddress(hMSS, "_AIL_set_3D_speaker_type@8");
	pAIL_set_3D_user_data = GetProcAddress(hMSS, "_AIL_set_3D_user_data@12");
	pAIL_set_3D_velocity = GetProcAddress(hMSS, "_AIL_set_3D_velocity@20");
	pAIL_set_3D_velocity_vector = GetProcAddress(hMSS, "_AIL_set_3D_velocity_vector@16");
	pAIL_set_DLS_processor = GetProcAddress(hMSS, "_AIL_set_DLS_processor@12");
	pAIL_set_DirectSound_HWND = GetProcAddress(hMSS, "_AIL_set_DirectSound_HWND@8");
	pAIL_set_XMIDI_master_volume = GetProcAddress(hMSS, "_AIL_set_XMIDI_master_volume@8");
	pAIL_set_digital_driver_processor = GetProcAddress(hMSS, "_AIL_set_digital_driver_processor@12");
	pAIL_set_digital_master_reverb = GetProcAddress(hMSS, "_AIL_set_digital_master_reverb@16");
	pAIL_set_digital_master_reverb_levels = GetProcAddress(hMSS, "_AIL_set_digital_master_reverb_levels@12");
	pAIL_set_digital_master_room_type = GetProcAddress(hMSS, "_AIL_set_digital_master_room_type@8");
	pAIL_set_digital_master_volume_level = GetProcAddress(hMSS, "_AIL_set_digital_master_volume_level@8");
	pAIL_set_error = GetProcAddress(hMSS, "_AIL_set_error@4");
	pAIL_set_file_async_callbacks = GetProcAddress(hMSS, "_AIL_set_file_async_callbacks@20");
	pAIL_set_file_callbacks = GetProcAddress(hMSS, "_AIL_set_file_callbacks@16");
	pAIL_set_filter_DLS_preference = GetProcAddress(hMSS, "_AIL_set_filter_DLS_preference@12");
	pAIL_set_filter_preference = GetProcAddress(hMSS, "_AIL_set_filter_preference@12");
	pAIL_set_filter_sample_preference = GetProcAddress(hMSS, "_AIL_set_filter_sample_preference@12");
	pAIL_set_filter_stream_preference = GetProcAddress(hMSS, "_AIL_set_filter_stream_preference@12");
	pAIL_set_input_state = GetProcAddress(hMSS, "_AIL_set_input_state@8");
	pAIL_set_named_sample_file = GetProcAddress(hMSS, "_AIL_set_named_sample_file@20");
	pAIL_set_preference = GetProcAddress(hMSS, "_AIL_set_preference@8");
	pAIL_set_redist_directory = GetProcAddress(hMSS, "_AIL_set_redist_directory@4");
	pAIL_set_sample_address = GetProcAddress(hMSS, "_AIL_set_sample_address@12");
	pAIL_set_sample_adpcm_block_size = GetProcAddress(hMSS, "_AIL_set_sample_adpcm_block_size@8");
	pAIL_set_sample_file = GetProcAddress(hMSS, "_AIL_set_sample_file@12");
	pAIL_set_sample_loop_block = GetProcAddress(hMSS, "_AIL_set_sample_loop_block@12");
	pAIL_set_sample_loop_count = GetProcAddress(hMSS, "_AIL_set_sample_loop_count@8");
	pAIL_set_sample_low_pass_cut_off = GetProcAddress(hMSS, "_AIL_set_sample_low_pass_cut_off@8");
	pAIL_set_sample_ms_position = GetProcAddress(hMSS, "_AIL_set_sample_ms_position@8");
	pAIL_set_sample_playback_rate = GetProcAddress(hMSS, "_AIL_set_sample_playback_rate@8");
	pAIL_set_sample_position = GetProcAddress(hMSS, "_AIL_set_sample_position@8");
	pAIL_set_sample_processor = GetProcAddress(hMSS, "_AIL_set_sample_processor@12");
	pAIL_set_sample_reverb_levels = GetProcAddress(hMSS, "_AIL_set_sample_reverb_levels@12");
	pAIL_set_sample_type = GetProcAddress(hMSS, "_AIL_set_sample_type@12");
	pAIL_set_sample_user_data = GetProcAddress(hMSS, "_AIL_set_sample_user_data@12");
	pAIL_set_sample_volume_levels = GetProcAddress(hMSS, "_AIL_set_sample_volume_levels@12");
	pAIL_set_sample_volume_pan = GetProcAddress(hMSS, "_AIL_set_sample_volume_pan@12");
	pAIL_set_sequence_loop_count = GetProcAddress(hMSS, "_AIL_set_sequence_loop_count@8");
	pAIL_set_sequence_ms_position = GetProcAddress(hMSS, "_AIL_set_sequence_ms_position@8");
	pAIL_set_sequence_tempo = GetProcAddress(hMSS, "_AIL_set_sequence_tempo@12");
	pAIL_set_sequence_user_data = GetProcAddress(hMSS, "_AIL_set_sequence_user_data@12");
	pAIL_set_sequence_volume = GetProcAddress(hMSS, "_AIL_set_sequence_volume@12");
	pAIL_set_stream_loop_block = GetProcAddress(hMSS, "_AIL_set_stream_loop_block@12");
	pAIL_set_stream_loop_count = GetProcAddress(hMSS, "_AIL_set_stream_loop_count@8");
	pAIL_set_stream_low_pass_cut_off = GetProcAddress(hMSS, "_AIL_set_stream_low_pass_cut_off@8");
	pAIL_set_stream_ms_position = GetProcAddress(hMSS, "_AIL_set_stream_ms_position@8");
	pAIL_set_stream_playback_rate = GetProcAddress(hMSS, "_AIL_set_stream_playback_rate@8");
	pAIL_set_stream_position = GetProcAddress(hMSS, "_AIL_set_stream_position@8");
	pAIL_set_stream_processor = GetProcAddress(hMSS, "_AIL_set_stream_processor@12");
	pAIL_set_stream_reverb_levels = GetProcAddress(hMSS, "_AIL_set_stream_reverb_levels@12");
	pAIL_set_stream_user_data = GetProcAddress(hMSS, "_AIL_set_stream_user_data@12");
	pAIL_set_stream_volume_levels = GetProcAddress(hMSS, "_AIL_set_stream_volume_levels@12");
	pAIL_set_stream_volume_pan = GetProcAddress(hMSS, "_AIL_set_stream_volume_pan@12");
	pAIL_set_timer_divisor = GetProcAddress(hMSS, "_AIL_set_timer_divisor@8");
	pAIL_set_timer_frequency = GetProcAddress(hMSS, "_AIL_set_timer_frequency@8");
	pAIL_set_timer_period = GetProcAddress(hMSS, "_AIL_set_timer_period@8");
	pAIL_set_timer_user = GetProcAddress(hMSS, "_AIL_set_timer_user@8");
	pAIL_shutdown = GetProcAddress(hMSS, "_AIL_shutdown@0");
	pAIL_size_processed_digital_audio = GetProcAddress(hMSS, "_AIL_size_processed_digital_audio@16");
	pAIL_start_3D_sample = GetProcAddress(hMSS, "_AIL_start_3D_sample@4");
	pAIL_start_all_timers = GetProcAddress(hMSS, "_AIL_start_all_timers@0");
	pAIL_start_sample = GetProcAddress(hMSS, "_AIL_start_sample@4");
	pAIL_start_sequence = GetProcAddress(hMSS, "_AIL_start_sequence@4");
	pAIL_start_stream = GetProcAddress(hMSS, "_AIL_start_stream@4");
	pAIL_start_timer = GetProcAddress(hMSS, "_AIL_start_timer@4");
	pAIL_startup = GetProcAddress(hMSS, "_AIL_startup@0");
	pAIL_stop_3D_sample = GetProcAddress(hMSS, "_AIL_stop_3D_sample@4");
	pAIL_stop_all_timers = GetProcAddress(hMSS, "_AIL_stop_all_timers@0");
	pAIL_stop_sample = GetProcAddress(hMSS, "_AIL_stop_sample@4");
	pAIL_stop_sequence = GetProcAddress(hMSS, "_AIL_stop_sequence@4");
	pAIL_stop_timer = GetProcAddress(hMSS, "_AIL_stop_timer@4");
	pAIL_stream_info = GetProcAddress(hMSS, "_AIL_stream_info@20");
	pAIL_stream_loop_count = GetProcAddress(hMSS, "_AIL_stream_loop_count@4");
	pAIL_stream_low_pass_cut_off = GetProcAddress(hMSS, "_AIL_stream_low_pass_cut_off@4");
	pAIL_stream_ms_position = GetProcAddress(hMSS, "_AIL_stream_ms_position@12");
	pAIL_stream_playback_rate = GetProcAddress(hMSS, "_AIL_stream_playback_rate@4");
	pAIL_stream_position = GetProcAddress(hMSS, "_AIL_stream_position@4");
	pAIL_stream_reverb_levels = GetProcAddress(hMSS, "_AIL_stream_reverb_levels@12");
	pAIL_stream_status = GetProcAddress(hMSS, "_AIL_stream_status@4");
	pAIL_stream_user_data = GetProcAddress(hMSS, "_AIL_stream_user_data@8");
	pAIL_stream_volume_levels = GetProcAddress(hMSS, "_AIL_stream_volume_levels@12");
	pAIL_stream_volume_pan = GetProcAddress(hMSS, "_AIL_stream_volume_pan@12");
	pAIL_true_sequence_channel = GetProcAddress(hMSS, "_AIL_true_sequence_channel@8");
	pAIL_unlock = GetProcAddress(hMSS, "_AIL_unlock@0");
	pAIL_unlock_mutex = GetProcAddress(hMSS, "_AIL_unlock_mutex@0");
	pAIL_update_3D_position = GetProcAddress(hMSS, "_AIL_update_3D_position@8");
	pAIL_us_count = GetProcAddress(hMSS, "_AIL_us_count@0");
	pAIL_waveOutClose = GetProcAddress(hMSS, "_AIL_waveOutClose@4");
	pAIL_waveOutOpen = GetProcAddress(hMSS, "_AIL_waveOutOpen@16");
	pDLSMSSGetCPU = GetProcAddress(hMSS, "_DLSMSSGetCPU@4");
	pMIX_RIB_MAIN = GetProcAddress(hMSS, "_MIX_RIB_MAIN@8");
	pRIB_enumerate_providers = GetProcAddress(hMSS, "_RIB_enumerate_providers@12");
	pRIB_find_file_dec_provider = GetProcAddress(hMSS, "_RIB_find_file_dec_provider@20");
	pRIB_find_files_provider = GetProcAddress(hMSS, "_RIB_find_files_provider@20");
	pRIB_find_provider = GetProcAddress(hMSS, "_RIB_find_provider@12");
	pRIB_load_application_providers = GetProcAddress(hMSS, "_RIB_load_application_providers@4");
	pRIB_load_static_provider_library = GetProcAddress(hMSS, "_RIB_load_static_provider_library@8");
	pRIB_provider_system_data = GetProcAddress(hMSS, "_RIB_provider_system_data@8");
	pRIB_provider_user_data = GetProcAddress(hMSS, "_RIB_provider_user_data@8");
	pRIB_set_provider_system_data = GetProcAddress(hMSS, "_RIB_set_provider_system_data@12");
	pRIB_set_provider_user_data = GetProcAddress(hMSS, "_RIB_set_provider_user_data@12");
	pstream_background = GetProcAddress(hMSS, "stream_background");

	miles32_loaded = true;
}