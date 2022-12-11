
/** $VER: PlaybackEventHandler.cpp (2022.12.11) P. Stuer **/

#include "framework.h"

#pragma hdrstop

namespace
{
    double _PreviewStartTime = 0.0;

    /// <summary>
    /// Handles the playback events we're subscribed to.
    /// </summary>
    class PlaybackEventHandler : public play_callback_static
    {
    public:
        /// <summary>
        /// Controls which methods your callback wants called; returned value should not change in run time, you should expect it to be queried only once (on startup). See play_callback::flag_* constants.
        /// </summary>
        virtual unsigned get_flags() final
        {
            return flag_on_playback_new_track | flag_on_playback_time | flag_on_playback_stop;
        }

        /// <summary>
        /// Playback process is being initialized. on_playback_new_track() should be called soon after this when first file is successfully opened for decoding.
        /// </summary>
        virtual void on_playback_starting(play_control::t_track_command, bool) final { }

        /// <summary>
        /// Playback advanced to new track.
        /// </summary>
        virtual void on_playback_new_track(metadb_handle_ptr track) final
        {
            if (!_IsPreviewing)
                return;

            // Get the track length.
            double TrackLength = track->get_length();

            // Get the preview start time.
            StartTimeTypes StartTimeType = GetStartTimeType();

            if (StartTimeType == StartTimeTypes::Seconds)
            {
                _PreviewStartTime = GetPreviewStartTimeInSec();
            }
            else
            if (StartTimeType == StartTimeTypes::Percentage)
            {
                double PreviewStartTimeAsPercentage = GetPreviewStartTimeAsPercentage();

                _PreviewStartTime = ((double)TrackLength * PreviewStartTimeAsPercentage) / 100.0;
            }
            else
            if (StartTimeType == StartTimeTypes::Random)
            {
                std::random_device RandomGenerator; // Obtain a random number from hardware.
                std::mt19937 Seed(RandomGenerator()); // Seed the generator.
                std::uniform_int_distribution<> UniformDistribution(0, (int)TrackLength); // Define the range.

                _PreviewStartTime = UniformDistribution(Seed);
            }

            if (_PreviewStartTime > 0.0)
            {
                // Queue a callback object to be called from main thread.
                static_api_ptr_t<main_thread_callback_manager> _MainThreadCallbackManager;

                service_ptr_t<SeekCallback> Callback = new service_impl_t<SeekCallback>();

                _MainThreadCallbackManager->add_callback(Callback);
            }
        }

        /// <summary>
        /// Playback stopped.
        /// </summary>
        virtual void on_playback_stop(play_control::t_stop_reason reason) final
        {
            if (!_IsPreviewing)
                return;

            // Stop Preview playback mode when the user stops the playback or if we reach the last track of the playlist.
            if ((reason == play_control::t_stop_reason::stop_reason_user) || (reason == play_control::t_stop_reason::stop_reason_eof))
                _IsPreviewing = false;
        }

        /// <summary>
        /// The user has seeked to a specific time.
        /// </summary>
        virtual void on_playback_seek(double) final { }

        /// <summary>
        /// Playback paused/resumed.
        /// </summary>
        virtual void on_playback_pause(bool) final { }

        /// <summary>
        /// Current track gets edited.
        /// </summary>
        virtual void on_playback_edited(metadb_handle_ptr) final { }

        /// <summary>
        /// Dynamic info f.e. VBR bitrate changed.
        /// </summary>
        virtual void on_playback_dynamic_info(const file_info &) final { }

        /// <summary>
        /// Per-track dynamic info (stream track titles etc) changed. Happens less often than on_playback_dynamic_info().
        /// </summary>
        virtual void on_playback_dynamic_info_track(const file_info &) final { }

        /// <summary>
        /// Called every second, for time display
        /// </summary>
        virtual void on_playback_time(double time) final
        {
            if (!_IsPreviewing)
                return;

            double PreviewEndTime = _PreviewStartTime + GetPreviewLength();

            if (time > PreviewEndTime)
            {
                // Queue a callback object to be called from main thread.
                static_api_ptr_t<main_thread_callback_manager> _MainThreadCallbackManager;

                service_ptr_t<StartPlaybackCallback> Callback = new service_impl_t<StartPlaybackCallback>();

                _MainThreadCallbackManager->add_callback(Callback);
            }
        }

        /// <summary>
        /// User changed volume settings. Possibly called when not playing.
        /// @param p_new_val new volume level in dB; 0 for full volume.
        /// </summary>
        virtual void on_volume_change(float) final { }

    private:
        /// <summary>
        /// Executes an action on the main thread.
        /// </summary>
        class StartPlaybackCallback : public main_thread_callback
        {
        public:
            void callback_run() noexcept
            {
                static_api_ptr_t<playback_control>()->start(playback_control::track_command_next, false);
            }
        };

        /// <summary>
        /// Executes an action on the main thread.
        /// </summary>
        class SeekCallback : public main_thread_callback
        {
        public:
            void callback_run() noexcept
            {
                static_api_ptr_t<playback_control>()->playback_seek(_PreviewStartTime);
            }
        };
    };

    static play_callback_static_factory_t<PlaybackEventHandler> _PlaybackEventHandler;
}
